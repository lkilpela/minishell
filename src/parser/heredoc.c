/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:20:47 by aklein            #+#    #+#             */
/*   Updated: 2024/06/12 07:24:58 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_strjoin_free(char *free_me, char const *dont_free_me)
{
	char	*new_string;

	new_string = ft_strjoin(free_me, dont_free_me);
	free(free_me);
	return (new_string);
}

static char	*heredoc_exp(char *str_start)
{
	char	*str;

	str = str_start;
	while (*str)
	{
		if (*str == '$')
			str = exp_next_var(str, &str_start);
		else
			str++;
	}
	return (str_start);
}

void	check_line(t_cmd *cmd, char *line)
{
	static int	line_count = 0;

	line_count++;
	if (!line)
	{
		ft_putstr_fd(HD_EOF1, 2);
		ft_putnbr_fd(line_count, 2);
		ft_putstr_fd(HD_EOF2, 2);
		ft_putstr_fd(cmd->heredoc_delim, 2);
		ft_putendl_fd(HD_EOF3, 2);
		ms_exit(FATAL, EXIT_SUCCESS);
	}
}

char	*heredoc(t_cmd *cmd)
{
	char	*line;
	char	*str;
	char	*tmp;

	str = ft_safe_calloc(1, sizeof(char));
	set_signals(SIG_HD);
	while (42)
	{
		line = readline("> ");
		check_line(cmd, line);
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_safe_strjoin(str, ft_strjoin_free(line, "\n"));
		ft_free((void **)&str);
		str = tmp;
	}
	set_signals(SIG_FORK);
	if (cmd->heredoc_expand)
		str = heredoc_exp(str);
	return (str);
}

t_token_list	*handle_heredoc(t_cmd *cmd, t_token_list *tokens)
{
	cmd->in_file.type = HEREDOC;
	tokens = tokens->next;
	tokens->expand = 0;
	if (!has_quotes(tokens->value))
		cmd->heredoc_expand = 1;
	tokens->value = handle_node_quotes(tokens->value);
	cmd->heredoc_delim = tokens->value;
	cmd->in_file.file = tokens->value;
	cmd->in_file.fd = -1;
	add_redir(&cmd->in_file, cmd);
	return (tokens);
}
