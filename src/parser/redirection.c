/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/31 01:04:17 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//returning empty string on error, maybe need NULL idk
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
		if (!strcmp(line, cmd->heredoc_delim))
		{
			ft_free((void **)&line);
			break ;
		}
		tmp = ft_safe_strjoin(str, line);
		ft_free((void **)&str);
		str = tmp;
		ft_putstr_fd("> ", 1);
		ft_free((void **)&line);
		line = get_next_line(0);
	}
	str = heredoc_exp(str);
	return (str);
}

int	has_quotes(char *value)
{
	while (*value)
	{
		if (is_quote(*value))
			return (1);
		value++;
	}
	return (0);
}

int	contains_space(char *var)
{
	char	quote;

	quote = 0;
	while (*var)
	{
		if (!quote && is_whitespace(*var))
			return (1);
		if (!quote && is_quote(*var))
			quote = *var;
		else if (quote && *var == quote)
			quote = 0;
		var++;
	}
	return (0);
}

t_token_list	*handle_heredoc(t_cmd *simple, t_token_list *tokens)
{
	tokens = tokens->next;
	tokens->expand = 0;
	if (!has_quotes(tokens->value))
		simple->heredoc_expand = 1;
	tokens->value = handle_node_quotes(tokens->value);
	simple->heredoc_delim = ft_safe_strjoin(tokens->value, "\n");
	simple->heredoc = heredoc(simple);
	printf("%s", simple->heredoc); //temp
	return (tokens->next);
}

int	is_ambiguous(char *val, t_token_list *tokens)
{
	if (contains_space(val))
	{
		print_error("minishell: ", tokens->value, ERR_AMBIGUOUS, 0);
		ms()->exit = 1;
		return (1);
	}
	return (0);
}

t_token_list	*handle_input_redir(t_cmd *simple, t_token_list *tokens)
{
	char	*val;

	if (simple->heredoc)
		ft_free((void **)&simple->heredoc);
	tokens = tokens->next;
	if (tokens->type == WORD)
	{
		val = exp_word(tokens->value);
		if (is_ambiguous(val, tokens))
			simple->in_file.file = NULL;
		else
		{
			tokens->value = val;
			simple->in_file.file = tokens->value;
		}
		return (tokens->next);
	}
	return (tokens);
}

t_token_list	*handle_output_redir(t_cmd *simple, t_token_list *tokens)
{
	char	*val;

	simple->out_file.append = 0;
	if (tokens->type == OP_DGREAT)
		simple->out_file.append = 1;
	tokens = tokens->next;
	if (tokens->type == WORD)
	{
		val = exp_word(tokens->value);
		if (is_ambiguous(val, tokens))
			simple->out_file.file = NULL;
		else
		{
			tokens->value = val;
			simple->out_file.file = tokens->value;
		}
		return (tokens->next);
	}
	return (tokens);
}

t_token_list	*get_redir(t_cmd *cmd, t_token_list *t)
{
	if (t->type == OP_DLESS)
		t = handle_heredoc(cmd, t);
	else if (t->type == OP_LESS)
		t = handle_input_redir(cmd, t);
	else if (t->type == OP_GREAT || t->type == OP_DGREAT)
		t = handle_output_redir(cmd, t);
	return (t);
}
