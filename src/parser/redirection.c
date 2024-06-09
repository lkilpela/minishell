/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:04:59 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/09 03:20:40 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_redir(t_redir *redir, t_cmd	*cmd)
{
	t_list	*node;
	t_redir	*new;

	if (redir->file)
	{
		new = ft_safe_calloc(1, sizeof(t_redir));
		*new = *redir;
		node = ft_safe_lstnew(new);
		ft_lstadd_back(&cmd->redirs, node);
	}
}

static t_token_list	*handle_input_redir(t_cmd *cmd, t_token_list *tokens)
{
	char	*val;

	cmd->in_file.type = INFILE;
	tokens = tokens->next;
	if (tokens->type == WORD)
	{
		val = exp_word(tokens->value);
		if (is_ambiguous(val, tokens))
			cmd->in_file.file = NULL;
		else
		{
			val = handle_node_quotes(val);
			tokens->value = val;
			cmd->in_file.file = tokens->value;
		}
		add_redir(&cmd->in_file, cmd);
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
			val = handle_node_quotes(val);
			tokens->value = val;
			cmd->out_file.file = tokens->value;
		}
		add_redir(&cmd->out_file, cmd);
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
