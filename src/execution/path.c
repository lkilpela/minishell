/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/03 12:12:52 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**get_path_dirs(void)
{
	t_var_list	*var;

	var = ms()->var_list;
	while (var)
	{
		if (ft_strcmp(var->key, "PATH") == 0)
			return (ft_split(var->value, ':'));
		var = var->next;
	}
	return (NULL);
}

void	init_path_dirs(void)
{
	if (!ms()->paths)
		ms()->paths = get_path_dirs();
}

char	*find_executable(t_cmd *cmd)
{
	char	*command;
	char	*tmp;
	int		i;

	command = NULL;
	tmp = NULL;
	i = 0;
	if (!ft_strchr(cmd->command, '/'))
		command = ft_safe_strjoin("/", cmd->command);
	else
		return (ft_safe_strdup(cmd->command));
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		if (!tmp || access(tmp, F_OK | X_OK) == 0)
		{
			cmd->exec_path = tmp;
			return (cmd->exec_path);
		}
		ft_free((void **)&tmp);
		i++;
	}
	ft_free((void **)&command);
	return (NULL);
}
