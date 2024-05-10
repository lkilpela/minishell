/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:37:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/10 14:39:31 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// find the environment path for Unix commands (e.g grep, ls, cat, etc.)
static char	**get_envpaths(t_minishell *m)
{
	int	i;

	i = 0;
	while (m->envp[i] && ft_strncmp(m->envp[i], "PATH=", 5) != 0)
		i++;
	if (!m->envp[i] || ft_strlen(m->envp[i]) < 5)
		return (NULL);
	return (ft_split(m->envp[i] + 5, ':'));
}

// concatenates the directory, '/' & cmd to form a full path to the executable
static char	*find_executable(t_minishell *m, char *cmd)
{
	char	*path;
	char	*command;
	int		i;

	command = ft_strjoin("/", cmd);
	if (!command)
		return (NULL);
	i = 0;
	while (m->paths[i])
	{
		path = ft_strjoin(m->paths[i], command);
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
char	*find_command(t_minishell *m, char *cmd)
{
	if (!cmd)
		return (NULL);
	else if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	if (!m->paths)
		p->paths = get_envpaths(p);
	if (!m->paths)
		return (NULL);
	return (find_executable(m, cmd));
}