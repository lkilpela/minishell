/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 04:20:30 by lkilpela         ###   ########.fr       */
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
		if (!ft_strcmp(line, cmd->heredoc_delim))
			break ;
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

static t_token_list	*handle_heredoc(t_cmd *cmd, t_token_list *tokens)
{
	cmd->in_file.type = INFILE;
	if (cmd->in_file.file)
		ft_free((void **)&cmd->in_file.file);
	if (cmd->heredoc)
		ft_free((void **)&cmd->heredoc);
	tokens = tokens->next;
	tokens->expand = 0;
	if (!has_quotes(tokens->value))
		cmd->heredoc_expand = 1;
	tokens->value = handle_node_quotes(tokens->value);
	cmd->heredoc_delim = ft_safe_strjoin(tokens->value, "\n");
	cmd->heredoc = heredoc(cmd);
	return (tokens->next);
}

static t_token_list	*handle_input_redir(t_cmd *cmd, t_token_list *tokens)
{
	char	*val;

	cmd->in_file.type = INFILE;
	if (cmd->heredoc)
		ft_free((void **)&cmd->heredoc);
	tokens = tokens->next;
	if (tokens->type == WORD)
	{
		val = exp_word(tokens->value);
		if (is_ambiguous(val, tokens))
			cmd->in_file.file = NULL;
		else
		{
			tokens->value = val;
			cmd->in_file.file = tokens->value;
		}
		return (tokens->next);
	}
	return (tokens);
}

static t_token_list	*handle_output_redir(t_cmd *cmd, t_token_list *tokens)
{
	char	*val;

	cmd->out_file.type = OUTFILE;
	cmd->out_file.append = 0;
	if (tokens->type == OP_DGREAT)
		cmd->out_file.append = 1;
	tokens = tokens->next;
	if (tokens->type == WORD)
	{
		val = exp_word(tokens->value);
		if (is_ambiguous(val, tokens))
			cmd->out_file.file = NULL;
		else
		{
			tokens->value = val;
			cmd->out_file.file = tokens->value;
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
