/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:18:43 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 21:39:33 by aklein           ###   ########.fr       */
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
			add_var(cmd->args[i]);
			i++;
		}
	}
}
