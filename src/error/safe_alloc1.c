/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:31:25 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 05:33:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_lstnew(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)node);
	return (node);
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
