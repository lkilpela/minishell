/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:18:43 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 03:07:15 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_export(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->num_of_args == 0)
	{
		built_env(1);
		return ;
	}
	if (cmd->num_of_args >= 1)
	{
		while (i < cmd->num_of_args)
		{
			if (!env_is_env(cmd->args[i]))
				continue ;
			env_add(cmd->args[i]);
			i++;
		}
	}
}
