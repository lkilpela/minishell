/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:20:47 by aklein            #+#    #+#             */
/*   Updated: 2024/06/12 12:25:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static int	check_line(t_cmd *cmd, char *line)
{
	static int	line_count = 0;

	line_count++;
	if (ms()->interrupt)
	{
		line_count = 0;
		free(line);
		return (0);
	}
	if (!line)
	{
		ft_putstr_fd(HD_EOF1, 2);
		ft_putnbr_fd(line_count, 2);
		ft_putstr_fd(HD_EOF2, 2);
		ft_putstr_fd(cmd->heredoc_delim, 2);
		ft_putendl_fd(HD_EOF3, 2);
		line_count = 0;
		return (0);
	}
	return (1);
}

char	*heredoc(t_cmd *cmd)
{
	char	*line;
	char	*str;
	char	*tmp;
	int		stdin_backup;

	stdin_backup = dup(0);
	str = ft_safe_calloc(1, sizeof(char));
	while (42)
	{
		line = readline("> ");
		if (!check_line(cmd, line))
			break ;
		if (ft_strcmp(line, cmd->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_safe_strjoin(str, ft_safe_strjoin(line, "\n"));
		ft_free((void **)&str);
		str = tmp;
	}
	if (cmd->heredoc_expand)
		str = heredoc_exp(str);
	safe_dup2(stdin_backup, 0);
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
	set_signals(SIG_HD);
	cmd->in_file.file = heredoc(cmd);
	if (!ms()->interrupt)
		set_signals(SIG_MAIN);
	cmd->in_file.fd = -1;
	add_redir(&cmd->in_file, cmd);
	return (tokens);
}
