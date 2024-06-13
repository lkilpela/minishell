/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:31:25 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/13 03:43:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(count, size);
	if (!alloc)
		ft_error(EXIT_FAILURE);
	add_to_lal(alloc);
	return (alloc);
}

void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		ft_error(EXIT_FAILURE);
	safe_close(fd);
}

void	safe_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
			ft_error(EXIT_FAILURE);
	}
}

void	safe_pipe(int *pipedes)
{
	if (pipe(pipedes) == -1)
		ft_error(EXIT_FAILURE);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(EXIT_FAILURE);
	return (pid);
}
