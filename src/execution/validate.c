/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/31 17:05:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define PERMISSION 0644
# define O_INFILE O_RDONLY
# define O_OUTFILE O_CREAT | O_WRONLY | O_TRUNC
# define O_APPENDFILE O_CREAT | O_WRONLY | O_TRUNC //fix for append


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
			close (file->fd);
		file->fd = open(file->file, oflags, PERMISSION);
		if (file->fd == -1)
		{
			print_error("minishell", file->file, NULL, 1);
			return (0);
		}
	}
	else
		file->fd = -1;
	return (1);
}
