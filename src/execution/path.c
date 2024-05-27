/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 12:16:32 by lkilpela         ###   ########.fr       */
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
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		if (tmp && access(tmp, F_OK | X_OK) != -1)
		{
			a_cmd->executable = tmp;
			return (a_cmd->executable);
		}
		ft_free((void **)&tmp);
		i++;
	}
	ft_free((void **)&command);
	return (NULL);
}

void print_executable(t_commands *cmds)
{
	int i = 0;
	if (cmds == NULL)
	{
		ft_printf("NULL commands structure\n");
		return;
	}
	while (i < cmds->num_of_cmds)
	{
		ft_printf("\e[0;32mexecutable_cmd %d:\e[0m\n", i + 1);
		printf("%s\n", find_executable(cmds->simples[i]));
		i++;
	}
}