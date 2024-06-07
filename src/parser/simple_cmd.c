/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:14:03 by aklein            #+#    #+#             */
/*   Updated: 2024/06/07 21:11:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_current_el(t_token_list **tokens, t_token_list **index)
{
	char			*str;
	char			*new;
	t_token_list	*new_tokens;

	str = (*index)->value;
	if (ft_strchr(str, DOLLAR_SIGN))
	{
		new = exp_word(str);
		new_tokens = new_tokenizer(new);
		clear_token_quotes(new_tokens);
		list_to_list(tokens, new_tokens, index);
	}
	else
		(*index)->value = handle_node_quotes((*index)->value);
}

static int	count_args(t_token_list **tokens)
{
	int				count;
	t_token_list	*current;

	current = *tokens;
	current = current->next;
	count = 0;
	while (current && current->type != OP_PIPE)
	{
		if (current->type >= OP_LESS && current->type <= OP_DGREAT)
		{
			current = current->next;
			if (current->type == WORD)
				current = current->next;
			continue ;
		}
		if (current->type == WORD)
		{
			expand_current_el(tokens, &current);
			if (current && current->type == WORD)
				count++;
		}
		if (current)
			current = current->next;
	}
	return (count);
}

static void	init_args(t_cmd *cmd, t_token_list **tokens)
{
	cmd->num_of_args = count_args(tokens) + 1;
	cmd->args = ft_safe_calloc(cmd->num_of_args + 1, sizeof(char *));
	if (cmd->command)
		cmd->args[0] = cmd->command;
}

static void	parse_command(t_cmd *cmd, t_token_list **tokens)
{
	if ((*tokens)->type == WORD)
	{
		expand_current_el(tokens, tokens);
		if (*tokens != NULL)
		{
			cmd->command = (*tokens)->value;
		}
	}
	if (cmd->command)
		init_args(cmd, tokens);
}

int	local_var(t_cmd *cmd)
{
	if (cmd->command && ft_strchr(cmd->command, EQUAL_SIGN))
	{
		cmd->num_of_args = 1;
		cmd->command = ft_strdup("=");
		return (1);
	}
	return (0);
}

// int next_token(t_token_list **tokens, t_cmd **cmd)
// {
// 	if ((*tokens))
// 	{
// 		(*tokens) = (*tokens)->next;
// 	}
// 	if (local_var(cmd))
// 		return (0);
// 	return (1);
// }

void	get_all_redir(t_token_list *tokens, t_cmd *cmd)
{
	while (tokens && tokens->type != OP_PIPE)
	{
		if (tokens->type >= OP_LESS && tokens->type <= OP_DGREAT)
			tokens = get_redir(cmd, tokens);
		if (tokens)
			tokens = tokens->next;
	}
}

t_cmd	*simple_cmd(t_token_list **tokens)
{
	t_cmd	*cmd;
	t_token_list	*head;

	head = *tokens;
	cmd = init_cmd(*tokens);
	while ((*tokens) && (*tokens)->type != OP_PIPE)
	{
		if ((*tokens)->type >= OP_LESS && (*tokens)->type <= OP_DGREAT)
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type == WORD && cmd->command == NULL)
			parse_command(cmd, tokens);
		else if ((*tokens)->type == WORD)
			cmd->args[cmd->arg_index++] = (*tokens)->value;
		if (local_var(cmd))
		{
			list_to_list(&head, NULL, tokens);
			*tokens = head;
			safe_close(cmd->in_file.fd);
			safe_close(cmd->out_file.fd);
			ft_lstadd_back(&ms()->local_var_assign, ft_safe_lstnew(cmd));
			cmd = init_cmd(*tokens);
			continue ;
		}
		if ((*tokens))
			(*tokens) = (*tokens)->next;
	}
	return (cmd);
}
