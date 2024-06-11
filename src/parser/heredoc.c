/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:20:47 by aklein            #+#    #+#             */
/*   Updated: 2024/06/12 01:21:42 by aklein           ###   ########.fr       */
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

char	*heredoc_gnl(t_cmd *cmd)
{
	char	*line;
	char	*error;
	char	*error_end;


	line = get_next_line(0);
	if (!line)
	{
		cmd->heredoc_delim[ft_strlen(cmd->heredoc_delim) - 1] = 0;
		error = ft_safe_strjoin(ERR_HD_EOF, cmd->heredoc_delim);
		error_end = ft_safe_strjoin(error, "')");
		print_error(ERR_MS, "warning", error_end, 0);
		ft_free((void **)&error);
		ft_free((void **)&error_end);
		return (NULL);
	}
	add_to_lal(line);
	return (line);
}

static char	*heredoc(t_cmd *cmd)
{
	char	*line;
	char	*tmp;
	char	*str;

	ft_putstr_fd("> ", 1);
	line = heredoc_gnl(cmd);
	str = ft_safe_calloc(1, sizeof(char));
	while (line)
	{
		if (!ft_strcmp(line, cmd->heredoc_delim))
			break ;
		tmp = ft_safe_strjoin(str, line);
		ft_free((void **)&str);
		str = tmp;
		ft_putstr_fd("> ", 1);
		ft_free((void **)&line);
		line = heredoc_gnl(cmd);
	}
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
	cmd->heredoc_delim = ft_safe_strjoin(tokens->value, "\n");
	cmd->in_file.file = heredoc(cmd);
	cmd->in_file.fd = -1;
	add_redir(&cmd->in_file, cmd);
	return (tokens);
}
