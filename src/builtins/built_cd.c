/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/05/30 17:48:01 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_cd(t_cmd *cmd)
{
	char	*home;

	if (cmd->num_of_args > 1)
	{
		ft_error(WARNING, "cd: too many arguments", 1);
		ms()->exit = 1;
		return ;
	}
	if (cmd->num_of_args == 0)
	{
		home = lookup_var("HOME");
		if (*home == 0)
		{
			ft_error(WARNING, "cd: HOME not set", 1);
			ms()->exit = 1;
			return ;
		}
		if (chdir(home) == 0)
			ft_free((void **)&home);
	}
	if (cmd->num_of_args == 1)
		if (chdir(cmd->args[0]) != 0)
		{
			print_error("minishell: cd", cmd->args[0], NULL, 1);
			ms()->exit = 1;
			return ;
		}
}
