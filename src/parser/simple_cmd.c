/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:03:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 22:55:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	expand_current_el(t_token_list **tokens)
{
	char			*str;
	char			*new;
	t_token_list	*new_tokens;
	t_token_list	*index;
	
	index = *tokens;
	str = (*tokens)->value;
	new = exp_word(str);
	new_tokens = new_tokenizer(new);
	list_to_list(tokens, new_tokens, index);
}

static int	count_args(t_token_list **_tokens)
{
	int	count;
	t_token_list	*tokens;

	tokens = *_tokens;
	count = 0;
	while (tokens && tokens->type != OP_PIPE)
	{
		if (tokens->type >= OP_LESS && tokens->type <= OP_DGREAT)
		{
			tokens = tokens->next;
			if (tokens->type == WORD)
				tokens = tokens->next;
			continue ;
		}
		expand_current_el(&tokens);
		if (tokens->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	parse_command(t_simple_cmd **simp, t_token_list **tokens)
{
	if ((*tokens)->type == WORD)
	{
		expand_current_el(tokens);
		(*simp)->command = (*tokens)->value;
		(*tokens) = (*tokens)->next;
	}
}

static void	parse_args(t_simple_cmd **simp, t_token_list **tokens)
{
	(*simp)->num_of_args = count_args(tokens);
	if ((*simp)->num_of_args > 0)
		(*simp)->args = ft_safe_calloc((*simp)->num_of_args, sizeof(char *));
}

t_simple_cmd	*simple_cmd(t_token_list **tokens)
{
	t_simple_cmd	*simple_cmd;
	int				i;

	i = 0;
	simple_cmd = ft_safe_calloc(1, sizeof(t_simple_cmd));
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
			parse_args(&simple_cmd, tokens);
			continue ;
		}
		if (simple_cmd->command != NULL && (*tokens)->type == WORD)
			simple_cmd->args[i++] = (*tokens)->value;
		(*tokens) = (*tokens)->next;
	}
	return (simple_cmd);
}

