/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/01 02:44:38 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define PERMISSION 0644
# define O_INFILE O_RDONLY
# define O_OUTFILE (O_CREAT | O_WRONLY | O_TRUNC)
# define O_APPENDFILE (O_CREAT | O_WRONLY | O_APPEND)


int	validate_redir(t_redir *file)
{
	int oflags;
	if (file->type == INFILE)
		oflags = O_INFILE;	
	if (file->type == OUTFILE)
		oflags = O_OUTFILE;
	if (file->append)
		oflags = O_APPENDFILE;
	if (file->file)
	{
		if (file->fd != -1)
		{
			printf("validate_redir: Closed file '%s' with file descriptor %d\n", file->file, file->fd);
			close (file->fd);
		}
		file->fd = open(file->file, oflags, PERMISSION);
		if (file->fd == -1)
		{
			print_error("minishell", file->file, NULL, 1);
			return (0);
		}
		printf("validate_redir: Opened file '%s' with file descriptor %d\n", file->file, file->fd);
		if (file->fd == STDIN_FILENO || file->fd == STDOUT_FILENO || file->fd == STDERR_FILENO)
			printf("validate_redir: Conflict: file descriptor %d overlaps with standard I/O\n", file->fd);
	}
	else
		file->fd = -1;
	return (1);
}
