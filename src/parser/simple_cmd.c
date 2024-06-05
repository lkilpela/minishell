/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:14:03 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 19:06:44 by aklein           ###   ########.fr       */
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
}

static void	parse_args(t_cmd *cmd, t_token_list **tokens)
{
	cmd->num_of_args = count_args(tokens) + 1;
	cmd->args = ft_safe_calloc(cmd->num_of_args + 1, sizeof(char *));
	if (cmd->command)
		cmd->args[0] = cmd->command;
}

t_cmd	*simple_cmd(t_token_list **tokens)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = ft_safe_calloc(1, sizeof(t_cmd));
	init_redir(cmd);
	while ((*tokens) && (*tokens)->type != OP_PIPE)
	{
		if ((*tokens)->type >= OP_LESS && (*tokens)->type <= OP_DGREAT)
			(*tokens) = get_redir(cmd, *tokens);
		else if ((*tokens)->type == WORD && cmd->command == NULL)
		{
			parse_command(cmd, tokens);
			parse_args(cmd, tokens);
			i = 1;
		}
		else if ((*tokens)->type == WORD)
			cmd->args[i++] = (*tokens)->value;
		if ((*tokens))
			(*tokens) = (*tokens)->next;
	}
	return (cmd);
}
