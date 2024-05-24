/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 12:05:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*heredoc(t_token_list *tokens)
{
	char	*line;
	char	*heredoc;
	char	*here_temp;
	char	*delim;

	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	heredoc = ft_calloc(1, 1);
	if (tokens->token->type != WORD)
		return (heredoc);
	delim = tokens->token->value;
	while (line)
	{
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			return (heredoc);
		}
		here_temp = ft_strdup(heredoc);
		free(heredoc);
		heredoc = ft_strjoin(here_temp, line);
		free(here_temp);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	return (heredoc); //no delim warning (bash: warning: here-document at line 1 delimited by end-of-file (wanted `<delimiter-value>'))
}

t_token_list	*get_redir(t_simple_cmd *simple, t_token_list *tokens)
{
	if (tokens->token->type == OP_DLESS)
	{
		tokens = tokens->next;
		simple->heredoc = heredoc(tokens);
	}
	if (tokens->token->type == OP_LESS)
	{
		if (simple->heredoc)
		{
			free(simple->heredoc);
			simple->heredoc = NULL;
		}
		tokens = tokens->next;
		if (tokens->token->type == WORD)
		{
			simple->in_file.file = tokens->token->value;
			return (tokens->next);
		}
	}
	if (tokens->token->type == OP_GREAT || tokens->token->type == OP_DGREAT)
	{
		simple->out_file.append = 0;
		if (tokens->token->type == OP_DGREAT)
			simple->out_file.append = 1;
		tokens = tokens->next;
		if (tokens->token->type == WORD)
		{
			simple->out_file.file = tokens->token->value;
			return (tokens->next);
		}
	}
	return (tokens);
}
