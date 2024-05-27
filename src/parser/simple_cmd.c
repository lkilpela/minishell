/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:03:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 06:46:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_args(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token->type != OP_PIPE)
	{
		if (tokens->token->type >= OP_LESS && tokens->token->type <= OP_DGREAT)
		{
			tokens = tokens->next;
			if (tokens->token->type == WORD)
				tokens = tokens->next;
			continue ;
		}
		if (tokens->token->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	parse_command(t_simple_cmd **simp, t_token_list **tokens)
{
	if ((*tokens)->token->type == WORD)
	{
		(*simp)->command = (*tokens)->token->value;
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
	while ((*tokens) && (*tokens)->token->type != OP_PIPE)
	{
		if ((*tokens)->token->type >= OP_LESS && (*tokens)->token->type <= OP_DGREAT)
		{
			(*tokens) = get_redir(simple_cmd, *tokens);
			print_tokens(*tokens);
			continue ;
		}
		if (simple_cmd->command == NULL && (*tokens)->token->type == WORD)
		{
			parse_command(&simple_cmd, tokens);
			parse_args(&simple_cmd, tokens);
			continue ;
		}
		if (simple_cmd->command != NULL && (*tokens)->token->type == WORD)
		{
			if (simple_cmd->args != NULL)
				simple_cmd->args[i++] = (*tokens)->token->value;
		}
		(*tokens) = (*tokens)->next;
	}
	print_simple_cmd(simple_cmd);
	return (simple_cmd);
}
