/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/03 19:59:25 by aklein           ###   ########.fr       */
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
			safe_close(file->fd);
		file->fd = open(file->file, oflags, PERMISSION);
		if (file->fd == -1)
		{
			print_error(ERR_MS, file->file, NULL, 1);
			return (0);
		}
	}
	else
		file->fd = -1;
	return (1);
}

static int	is_directory(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->command, O_DIRECTORY);
	if (fd != -1)
	{
		safe_close(fd);
		return (1);
	}
	return (0);
}

void	validate_command(t_cmd *cmd)
{
	cmd->exec_path = find_executable(cmd);
	if (!validate_redir(&cmd->in_file) || !validate_redir(&cmd->out_file))
		ms_exit(FATAL, 2);
	if (is_directory(cmd))
	{
		print_error(ERR_MS, cmd->command, ERR_DIR, 0);
		ms_exit(FATAL, E_CODE_CMD_NEXEC);
	}		
	if (cmd->exec_path != NULL)
	{
		if (access(cmd->exec_path, X_OK) != 0)
		{
			print_error(ERR_MS, cmd->command, ERR_PERM, 0);
			ms_exit(FATAL, E_CODE_CMD_NEXEC);
		}
	}
	else
	{
		print_error(ERR_MS, cmd->command, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD);
	}
}
