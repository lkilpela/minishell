/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/16 07:39:04 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		cwd = safe_getcwd();
		ms()->paths = ft_safe_calloc(2, sizeof(char *));
		if (!cwd)
			return ;
		ms()->paths[0] = ft_safe_strdup(cwd);
		ft_free((void **)&cwd);
	}
}

static int	is_executable_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISREG(path_stat.st_mode) && (path_stat.st_mode & S_IXUSR))
		return (1);
	return (0);
}

char	*find_executable(t_cmd *cmd)
{
	char	*command;
	char	*tmp;
	int		i;

	command = NULL;
	tmp = NULL;
	i = 0;
	command = ft_safe_strjoin("/", cmd->command);
	fix_null_path();
	while (ms()->paths[i])
	{
		tmp = ft_safe_strjoin(ms()->paths[i], command);
		if (is_executable_file(tmp))
		{
			ft_free((void **)&command);
			return (tmp);
		}
		ft_free((void **)&tmp);
		i++;
	}
	ft_free((void **)&command);
	return (NULL);
}
