/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:31:25 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 13:56:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(count, size);
	if (!alloc)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal(alloc);
	return (alloc);
}

void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		ft_error(E_CODE_ERRNO + errno);
}

void	safe_close(int fd)
{
	if (fd == 0 || fd == 1 || fd == 2)
		printf("closing %d, maybe not good?\n", fd);
	if (fd != -1)
	{
		if (close(fd) == -1)
			ft_error(E_CODE_ERRNO + errno);
	}
}

void	safe_pipe(int *pipedes)
{
	if (pipe(pipedes) == -1)
		ft_error(E_CODE_ERRNO + errno);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(E_CODE_ERRNO + errno);
	return (pid);
}
