/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:03:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/30 17:56:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_current_el(t_token_list **tokens, t_token_list **index)
{
	char			*str;
	char			*new;
	t_token_list	*new_tokens;
	
	str = (*index)->value;
	if (ft_strchr(str, DOLLAR_SIGN))
	{
		new = exp_word(str);
		new = handle_node_quotes(new);
		new_tokens = new_tokenizer(new);
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
		current = current->next;
	}
	return (count);
}

static void	parse_command(t_cmd **simp, t_token_list **tokens)
{
	if ((*tokens)->type == WORD)
	{
		expand_current_el(tokens, tokens);
		(*simp)->command = (*tokens)->value;
		(*tokens) = (*tokens)->next;
	}
}

static void	parse_args(t_cmd *simp, t_token_list **tokens)
{
	simp->num_of_args = count_args(tokens);
	if (simp->num_of_args > 0)
		simp->args = ft_safe_calloc(simp->num_of_args + 1, sizeof(char *));
}

t_cmd	*simple_cmd(t_token_list **tokens)
{
	t_cmd	*simple_cmd;
	int				i;

	i = 0;
	simple_cmd = ft_safe_calloc(1, sizeof(t_cmd));
	while ((*tokens) && (*tokens)->type != OP_PIPE)
	{
		if ((*tokens)->type >= OP_LESS && (*tokens)->type <= OP_DGREAT)
		{
			(*tokens) = get_redir(simple_cmd, *tokens);
			continue ;
		}
		if (simple_cmd->command == NULL && (*tokens)->type == WORD)
		{
			parse_command(&simple_cmd, tokens);
			parse_args(simple_cmd, tokens);
			i = 0;
			continue ;
		}
		if (simple_cmd->command != NULL && (*tokens)->type == WORD)
			simple_cmd->args[i++] = (*tokens)->value;
		(*tokens) = (*tokens)->next;
	}
	return (simple_cmd);
}

