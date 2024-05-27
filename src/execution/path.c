/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 08:54:35 by lkilpela         ###   ########.fr       */
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
	char	*dir_path;

	i = 0;
	dir_path = ms()->paths[i];
	if (!ft_strchr(a_cmd, '/'))
		command = ft_safe_strjoin("/", a_cmd);
	else
		return (ft_safe_strdup(a_cmd));
	while (ms()->paths[i])
	{
		executable = ft_safe_strjoin(ms()->paths[i], a_cmd);
		if (access(executable, F_OK | X_OK) == 0)
			return (executable);
		i++;
	}
	return (NULL);
}

char	*find_local_command(t_simple_cmd *a_cmd)
{
	if (!a_cmd->command)
		return (NULL);
	if (!ms()->paths)
		ms()->paths = get_path_var();
	return (find_executable(a_cmd));
}
