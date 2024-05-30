/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:04:56 by aklein            #+#    #+#             */
/*   Updated: 2024/05/30 16:18:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_cmd(t_token_list *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->type == OP_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_cmds *parser(t_token_list *tokens)
{
	t_cmds			*cmds;
	t_simple_cmd	*new_cmd;
	
	cmds = ft_safe_calloc(1, sizeof(t_cmds));
	cmds->num_of_cmds = count_cmd(tokens);
	while (tokens)
	{
		new_cmd = simple_cmd(&tokens);
		ft_lstadd_back(&cmds->simp_cmds, ft_safe_lstnew(new_cmd));
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}
