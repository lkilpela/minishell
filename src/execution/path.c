/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 09:03:04 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_path_dirs()
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

char *find_executable(t_simple_cmd *a_cmd)
{
	char	*command;
	int		i;
	char	*executable;
	char	**dir_paths;

	i = 0;
	dir_paths = ms()->paths;
	if (!ft_strchr(a_cmd->command, '/'))
		command = ft_safe_strjoin("/", a_cmd->command);
	else
		return (ft_safe_strdup(a_cmd->command));
	while (dir_paths[i])
	{
		executable = ft_safe_strjoin(dir_paths[i], command);
		if (executable && access(executable, F_OK | X_OK) == 0)
		{
			ft_free((void **)&command);
			return (executable);
		}
		i++;
	}
	ft_free((void **)&command);
	return (NULL);
}

char	*find_local_command(t_simple_cmd *a_cmd)
{
	if (!a_cmd->command)
		return (NULL);
	if (!ms()->paths)
		ms()->paths = get_path_dirs();
	return (find_executable(a_cmd));
}
