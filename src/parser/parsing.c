/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:04:56 by aklein            #+#    #+#             */
/*   Updated: 2024/05/24 12:04:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	parse_command(t_simple_cmd **simp, t_token_list **tokens)
{
	if ((*tokens)->token->type == WORD)
	{
		(*simp)->command = (*tokens)->token->value;
		(*tokens) = (*tokens)->next;
	}
}

void	parse_args(t_simple_cmd **simp, t_token_list **tokens)
{
	(*simp)->num_of_args = count_args(*tokens);
	if ((*simp)->num_of_args > 0)
		(*simp)->args = ft_calloc((*simp)->num_of_args, sizeof(char *));
}

t_simple_cmd	*simple_cmd(t_token_list **tokens)
{
	t_simple_cmd	*simple_cmd;
	int				i;

	simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	while ((*tokens) && (*tokens)->token->type != OP_PIPE)
	{
		if ((*tokens)->token->type >= OP_LESS && (*tokens)->token->type <= OP_DGREAT)
		{
			(*tokens) = get_redir(simple_cmd, *tokens);
			continue ;
		}
		if (simple_cmd->command == NULL && (*tokens)->token->type == WORD)
		{
			parse_command(&simple_cmd, tokens);
			parse_args(&simple_cmd, tokens);
			i = 0;
			continue ;
		}
		if (simple_cmd->command != NULL && (*tokens)->token->type == WORD)
			simple_cmd->args[i++] = (*tokens)->token->value;
		(*tokens) = (*tokens)->next;
	}
	return (simple_cmd);
}

void	var_to_word(t_token_list *tokens)
{
	while (tokens && tokens->token)
	{
		if (tokens->token->type == VAR)
			tokens->token->type = WORD;
		tokens = tokens->next;
	}
}

t_commands	*parser(t_token_list *tokens)
{
	t_commands	*cmds;
	int	i;

	cmds = ft_calloc(1, sizeof(t_commands));
	cmds->num_of_cmds = count_cmd(tokens);
	cmds->simples = ft_calloc(cmds->num_of_cmds, sizeof(t_simple_cmd *));
	i = 0;
	while (tokens)
	{
		var_to_word(tokens); //maybe temp if we actually need the VAR type
		cmds->simples[i++] = simple_cmd(&tokens);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}
