/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:37:58 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/25 03:06:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <minishell.h>

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		ft_free((void **)&paths[i]);
		i++;
	}
	ft_free((void **)&paths);
}

void	cleanup(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->paths)
		free_paths(p->paths);
	while (i != 2)
	{
		if (p->cmds[i].args)
			free_paths(p->cmds[i].args);
		if (p->cmds[i].path)
			ft_free((void **)&p->cmds[i].path);
		i++;
	}
}

char	**resize_array(char **old_array, int old_count, int new_count)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = ft_safe_calloc(new_count + 1, sizeof(char *));
	while (i < old_count)
	{
		new_array[i] = old_array[i];
		i++;
	}
	ft_free((void **)&old_array);
	old_array = NULL;
	return (new_array);
}

void	close_all_fds(t_pipex *p)
{
	if (!p)
		return ;
	if (p->infilefd != -1)
		close(p->infilefd);
	if (p->outfilefd != -1)
		close(p->outfilefd);
	if (p->pipefd[0] != -1)
		close(p->pipefd[0]);
	if (p->pipefd[1] != -1)
		close(p->pipefd[1]);
}
