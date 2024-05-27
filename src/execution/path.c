/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 11:25:31 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_path_dirs(void)
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
	for (int i = 0; ms()->paths[i]; i++)
			printf("dir_paths: %s\n", ms()->paths[i]);
}

char	*find_executable(t_simple_cmd *a_cmd)
{
	char	*command = NULL;
	char	*tmp = NULL;
	int		i;
	//char	**dir_paths = NULL;

	i = 0;
	if (!ft_strchr(a_cmd->command, '/'))
		command = ft_safe_strjoin("/", a_cmd->command);
	else
		return (ft_safe_strdup(a_cmd->command));
	printf("command: %s\n", command);
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		printf("tmp: %s\n", tmp);
		if (tmp && access(tmp, F_OK | X_OK) != -1)
		{
			//ft_free((void **)&command);
			a_cmd->executable = tmp;
			return (a_cmd->executable);
		}
		//ft_free((void **)&tmp);
		i++;
	}
	//ft_free((void **)&command);
	printf("executable: %s\n", a_cmd->executable);
	return (NULL);
}
