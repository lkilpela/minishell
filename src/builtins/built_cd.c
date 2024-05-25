/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/05/25 03:06:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_cd(t_simple_cmd *cmd)
{
	char	*home;

	if (cmd->num_of_args > 1)
	{
		ft_error(WARNING, "cd: too many arguments", 1);
		return ;
	}
	if (cmd->num_of_args == 0)
	{
		home = lookup_var("HOME");
		if (*home == 0)
		{
			ft_error(WARNING, "cd: HOME not set", 1);
			return ;
		}
		if (chdir(home) == 0)
			ft_free((void **)&home);
	}
	if (cmd->num_of_args == 1)
		if (chdir(cmd->args[0]) != 0)
		{
			print_errno("cd", cmd->args[0], 1);
			return ;
		}
}
