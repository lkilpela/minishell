/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 03:20:47 by aklein            #+#    #+#             */
/*   Updated: 2024/06/09 03:21:04 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*heredoc(t_cmd *cmd)
{
	char	*line;
	char	*tmp;
	char	*str;

	str = ft_safe_calloc(1, 1);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	str = ft_safe_calloc(1, sizeof(char));
	if (!line)
		return (str);
	while (line)
	{
		if (!ft_strcmp(line, cmd->heredoc_delim))
			break ;
		tmp = ft_safe_strjoin(str, line);
		ft_free((void **)&str);
		str = tmp;
		ft_putstr_fd("> ", 1);
		ft_free((void **)&line);
		line = get_next_line(0);
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