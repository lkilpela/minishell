/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 10:03:07 by lkilpela         ###   ########.fr       */
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

char	*find_executable(t_simple_cmd *a_cmd)
{
	char	*command;
	char	*tmp;
	int		i;

	command = NULL;
	tmp = NULL;
	i = 0;
	if (!ft_strchr(a_cmd->command, '/'))
		command = ft_safe_strjoin("/", a_cmd->command);
	else
		return (ft_safe_strdup(a_cmd->command));
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		if (tmp && access(tmp, F_OK | X_OK) != -1)
		{
			a_cmd->exec_path = tmp;
			return (a_cmd->exec_path);
		}
		ft_free((void **)&tmp);
		i++;
	}
	ft_free((void **)&command);
	return (NULL);
}
