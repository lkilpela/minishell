/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:04:56 by aklein            #+#    #+#             */
/*   Updated: 2024/06/04 04:21:01 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*parser(t_token_list *tokens)
{
	t_cmd	*new_cmd;
	t_list	*cmd_list;

	cmd_list = NULL;
	while (tokens)
	{
		new_cmd = simple_cmd(&tokens);
		ft_lstadd_back(&cmd_list, ft_safe_lstnew(new_cmd));
		if (tokens)
			tokens = tokens->next;
	}
	ms()->cmds_num = ft_lstsize(cmd_list);
	return (cmd_list);
}
