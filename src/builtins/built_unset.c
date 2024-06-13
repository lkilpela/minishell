/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:00 by aklein            #+#    #+#             */
/*   Updated: 2024/06/13 04:32:18 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	var_remove(char *key)
{
	t_var_list	*vars;

	vars = ms()->var_list;
	if (!key)
		return ;
	while (vars)
	{
		if (ft_strcmp(key, vars->key) == 0)
		{
			if (vars->previous)
				vars->previous->next = vars->next;
			else
				ms()->var_list = vars->next;
			if (vars->next)
				vars->next->previous = vars->previous;
			ft_free((void **)&vars);
			vars = NULL;
			return ;
		}
		vars = vars->next;
	}
}

void	built_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->num_of_args)
		var_remove(cmd->args[i++]);
	ms()->exit = EXIT_SUCCESS;
}
