/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:03:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 22:47:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_args(t_token_list *tokens)
{
	int	count;

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
		(*simp)->command = (*tokens)->value;
		(*tokens) = (*tokens)->next;
	}
}

static void	parse_args(t_simple_cmd **simp, t_token_list **tokens)
{
	(*simp)->num_of_args = count_args(*tokens);
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
