/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:13:10 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 01:51:40 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	builtin_cmd(t_cmd *cmd)
{
	if (cmd->command)
	{
		if (ft_strcmp(cmd->command, "exit") == 0)
		{
			built_exit(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "pwd") == 0)
		{
			built_pwd(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "env") == 0)
		{
			built_env(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "echo") == 0)
		{
			built_echo(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "export") == 0)
		{
			built_export(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "unset") == 0)
		{
			built_unset(cmd);
			return (1);
		}
		if (ft_strcmp(cmd->command, "cd") == 0)
		{
			built_cd(cmd);
			return (1);
		}
	}
	return (0);
}
