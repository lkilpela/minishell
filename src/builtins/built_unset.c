/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:00 by aklein            #+#    #+#             */
/*   Updated: 2024/05/27 00:17:20 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_unset(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->num_of_args)
		var_remove(cmd->args[i++]);
	ms()->exit = 0;
}
