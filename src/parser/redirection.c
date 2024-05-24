/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 15:48:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*heredoc(t_token_list *t)
{
	char	*line;
	char	*delim;
	char	*tmp;
	char	*expanded = ft_calloc(1, 1);

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
			free(line);
			return (expanded);
		}
		else
		{
			char *old_expand = expanded;
			expanded = ft_strjoin(expanded, tmp);
			free(old_expand);
		}
		ft_putstr_fd("> ", 1);
		free(line);
		line = get_next_line(0);
	}
	free(expanded);
	return (NULL);
}

t_token_list	*handle_heredoc(t_simple_cmd *simple, t_token_list *t)
{
	t = t->next;
	if (!t)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		exit(EXIT_FAILURE);
	}
	simple->heredoc = heredoc(t);
	printf("%s", simple->heredoc);
	return (t);
}

t_token_list	*handle_input_redir(t_simple_cmd *simple, t_token_list *tokens)
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

t_token_list	*get_redir(t_simple_cmd *simple, t_token_list *tokens)
{
	if (tokens->token->type == OP_DLESS)
	{
		tokens = handle_heredoc(simple, tokens);
	}
	if (tokens->token->type == OP_LESS)
	{
		tokens = handle_input_redir(simple, tokens);
	}
	if (tokens->token->type == OP_GREAT || tokens->token->type == OP_DGREAT)
	{
		tokens = handle_output_redir(simple, tokens);
	}
	return (tokens);
}
