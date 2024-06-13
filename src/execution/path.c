/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/13 23:20:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**ft_safe_split(const char *s, char c)
{
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = ft_split(s, c);
	if (!str_arr)
		ft_error(EXIT_FAILURE);
	while (str_arr[i])
	{
		add_to_lal((void *)str_arr[i]);
		i++;
	}
	add_to_lal((void *)str_arr);
	return (str_arr);
}

void	clear_paths(void)
{
	int	i;

	if (!ms()->paths)
		return ;
	i = 0;
	while (ms()->paths[i])
	{
		ft_free((void **)&ms()->paths[i]);
		i++;
	}
	ft_free((void **)&ms()->paths);
}

char	**get_path_dirs(void)
{
	t_var_list	*var;

	var = ms()->var_list;
	while (var)
	{
		if (ft_strcmp(var->key, "PATH") == 0)
			return (ft_safe_split(var->value, ':'));
		var = var->next;
	}
	return (NULL);
}

static void	fix_null_path(void)
{
	char	*cwd;

	if (ms()->paths == NULL)
	{
		cwd = getcwd(NULL, 0);
		ms()->paths = ft_safe_calloc(2, sizeof(char *));
		ms()->paths[0] = ft_safe_strdup(cwd);
	}
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
	fix_null_path();
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		if (access(tmp, F_OK) == 0)
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
