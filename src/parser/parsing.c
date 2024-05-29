/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:04:56 by aklein            #+#    #+#             */
/*   Updated: 2024/05/29 15:31:29 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_cmd(t_token_list *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->token->type == OP_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_commands	*parser(t_token_list *tokens)
{
	t_commands	*cmds;
	int			i;

	cmds = ft_safe_calloc(1, sizeof(t_commands));
	cmds->num_of_cmds = count_cmd(tokens);
	cmds->simples = ft_safe_calloc(cmds->num_of_cmds, sizeof(t_simple_cmd *));
	i = 0;
	while (tokens)
	{
		cmds->simples[i++] = simple_cmd(&tokens);
		if (tokens)
			tokens = tokens->next;
	}
	//print_commands(cmds);
	return (cmds);
}
