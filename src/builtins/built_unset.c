/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:00 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 03:57:07 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_unset(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->num_of_args)
		env_remove(cmd->args[i++]);
}