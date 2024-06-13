/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/13 14:05:53 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_directory(char *cmd)
{
	int	fd;

	fd = open(cmd, O_DIRECTORY);
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
		if (is_directory(cmd->exec_path))
		{
			print_error(ERR_MS, cmd->command, ERR_DIR, 0);
			ms_exit(FATAL, E_CODE_CMD_NEXEC);
		}
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
}

void	validate_command(t_cmd *cmd)
{
	if (!*cmd->command)
	{
		print_error(ERR_MS, cmd->command, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
	if (get_builtin(cmd).name)
		return ;
	validate_executable(cmd);
}
