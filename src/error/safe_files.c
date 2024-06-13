/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 23:59:22 by aklein            #+#    #+#             */
/*   Updated: 2024/06/14 00:53:55 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_fds(void)
{
	int	fd;

	fd = 3;
	if (ms()->max_fd < 3)
		return ;
	while (fd <= ms()->max_fd)
	{
		close(fd);
		fd++;
	}
	ms()->max_fd = 2;
}

int	safe_open(char *file, int oflags, int mode)
{
	int		fd;

	fd = open(file, oflags, mode);
	if (fd != -1)
	{
		if (fd > ms()->max_fd)
			ms()->max_fd = fd;
	}
	return (fd);
}

void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}

int	safe_dup(int fd)
{
	int	new_fd;

	new_fd = dup(fd);
	if (new_fd == -1)
		ft_error(EXIT_FAILURE);
	if (fd > ms()->max_fd)
		ms()->max_fd = fd;
	return (new_fd);
}

void	safe_dup2(int fd, int fd2)
{
	if (dup2(fd, fd2) == -1)
		ft_error(EXIT_FAILURE);
	safe_close(fd);
}
