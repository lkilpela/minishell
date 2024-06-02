/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:00 by aklein            #+#    #+#             */
/*   Updated: 2024/06/02 23:37:24 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_unset(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->num_of_args)
		var_remove(cmd->args[i++]);
	ms()->exit = 0;
}
