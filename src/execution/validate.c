/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/06 15:40:15 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	validate_redir_list(t_cmd *cmd)
{
	t_redir	*redir;
	t_list	*redirs;

	redirs = cmd->redirs;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (!validate_redir(redir))
			return (0);
		if (redir->type == INFILE)
			cmd->in_file = *redir;
		if (redir->type == OUTFILE)
			cmd->out_file = *redir;
		redirs = redirs->next;
	}
	return (1);
}

int	validate_redir(t_redir *file)
{
	int	oflags;

	if (file->type == INFILE)
		oflags = O_INFILE;
	if (file->type == OUTFILE)
		oflags = O_OUTFILE;
	if (file->append)
		oflags = O_APPENDFILE;
	if (file->file)
	{
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

static void	validate_executable(t_cmd *cmd)
{
	cmd->exec_path = find_executable(cmd);
	if (cmd->exec_path != NULL)
	{
		if (access(cmd->exec_path, X_OK) == -1)
		{
			if (errno == ENOENT)
			{
				print_error(ERR_MS, cmd->command, ERR_FILE, 0);
				ms_exit(FATAL, E_CODE_CMD_NFOUND);
			}
			else if (errno == EACCES)
			{
				print_error(ERR_MS, cmd->command, ERR_PERM, 0);
				ms_exit(FATAL, E_CODE_CMD_NEXEC);
			}
		}
	}
	else
	{
		print_error(ERR_MS, cmd->command, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
}

void	validate_command(t_cmd *cmd)
{
	if (get_builtin(cmd).name)
		return ;
	if (is_directory(cmd))
	{
		print_error(ERR_MS, cmd->command, ERR_DIR, 0);
		ms_exit(FATAL, E_CODE_CMD_NEXEC);
	}
	validate_executable(cmd);
}
