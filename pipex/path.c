/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:08:08 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/03 08:08:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Find the environment path for Unix commands (e.g grep, ls, cat, etc.)
static char	**get_envpaths(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->envp[i] && ft_strncmp(p->envp[i], "PATH=", 5) != 0)
		i++;
	if (!p->envp[i] || ft_strlen(p->envp[i]) < 5)
		return (NULL);
	return (ft_split(p->envp[i] + 5, ':'));
}

// concatenates the directory, '/' & cmd to form a full path to the executable
static char	*find_executable(t_pipex *p, char *cmd)
{
	char	*path;
	char	*command;
	int		i;

	command = ft_strjoin("/", cmd);
	if (!command)
		return (NULL);
	i = 0;
	while (p->paths[i])
	{
		path = ft_strjoin(p->paths[i], command);
		if (!path || access(path, F_OK | X_OK) == 0)
		{
			free(command);
			return (path);
		}
		free(path);
		i++;
	}
	free(command);
	return (NULL);
}

// determining the full path of a command
//line 60: parse whole path, return whole parsed command
char	*find_command(t_pipex *p, char *cmd)
{
	if (!cmd)
		return (NULL);
	else if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!p->paths)
		p->paths = get_envpaths(p);
	if (!p->paths)
		return (NULL);
	return (find_executable(p, cmd));
}
