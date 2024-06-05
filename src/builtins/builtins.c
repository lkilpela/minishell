/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:13:10 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 08:28:14 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_builtin get_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (ms()->builtins[i].name)
	{
		if (!ft_strcmp(ms()->builtins[i].name, cmd->command))
			return (ms()->builtins[i]);
		i++;
	}
	return (ms()->builtins[i]);
}

int	is_special_builtin(t_cmd *cmd)
{
	t_builtin	builtin;

	builtin = get_builtin(cmd);
	if (builtin.special)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd)
{
	t_builtin	builtin;

	builtin = get_builtin(cmd);
	if (!builtin.name)
		return (0);
	//ft_printf("executing builtin: '%s'\n", cmd->command);
	builtin.func(cmd);
	return (1);
}

void	init_builtins(void)
{
	static t_builtin	builtins[] = {
	{"cd", built_cd, 1},
	{"echo", built_echo, 0},
	{"env", built_env, 0},
	{"exit", built_exit, 1},
	{"export", built_export, 1},
	{"pwd", built_pwd, 0},
	{"unset", built_unset, 1},
	{NULL, NULL, 0}
	};

	ms()->builtins = builtins;
}
