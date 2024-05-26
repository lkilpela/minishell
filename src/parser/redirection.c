/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/26 14:25:30 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void append_heredoc(char **heredoc, char *tmp)
{
	char *old_heredoc;

	old_heredoc = *heredoc;
	*heredoc = ft_safe_strjoin(*heredoc, tmp);
	ft_free((void **)&old_heredoc);
}
// cat <<END | grep "hello" | wc -l > output
static char	*heredoc(t_token_list *t)
{
	char	*line;
	char	*delim;
	char	*tmp;
	char	*heredoc;

	heredoc = ft_safe_calloc(1, 1);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	if (!line)
		return (NULL);
	delim = t->token->value;
	while (line)
	{	
		tmp = check_quotes_and_expand(line);
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			ft_free((void **)&line);
			return (heredoc);
		}
		else
			append_heredoc(&heredoc, tmp);
		ft_putstr_fd("> ", 1);
		ft_free((void **)&line);
		line = get_next_line(0);
	}
	ft_free((void **)&heredoc);
	return (NULL);
}

t_token_list	*handle_heredoc(t_simple_cmd *simple, t_token_list *t)
{
	t = t->next;
	simple->heredoc = heredoc(t);
	return (t);
}

t_token_list	*handle_input_redir(t_simple_cmd *simple, t_token_list *tokens)
{
	if (simple->heredoc)
	{
		ft_free((void **)&simple->heredoc);
		simple->heredoc = NULL;
	}
	tokens = tokens->next;
	if (tokens->token->type == WORD)
	{
		simple->in_file.file = tokens->token->value;
		return (tokens->next);
	}
	return (tokens);
}

t_token_list	*handle_output_redir(t_simple_cmd *simple, t_token_list *tokens)
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
	return (tokens);
}

t_token_list	*get_redir(t_simple_cmd *simple, t_token_list *t)
{
	if (t->token->type == OP_DLESS)
	{
		t = handle_heredoc(simple, t);
	}
	if (t->token->type == OP_LESS)
	{
		t = handle_input_redir(simple, t);
	}
	if (t->token->type == OP_GREAT || t->token->type == OP_DGREAT)
	{
		t = handle_output_redir(simple, t);
	}
	return (t);
}
