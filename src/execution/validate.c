/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/13 13:09:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	printf("validate_executable");
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
	printf("validate_command\n");
	if (!*cmd->command)
	{
		print_error(ERR_MS, cmd->command, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
	printf("1\n");
	if (get_builtin(cmd).name)
		return ;
	if (is_directory(cmd))
	{
		if (ft_strchr(cmd->command, '/'))
		{
			printf("here1\n");
			print_error(ERR_MS, cmd->command, ERR_DIR, 0);
			ms_exit(FATAL, E_CODE_CMD_NEXEC);
		}
		else if (access(cmd->command, X_OK) != 0)
		{
			printf("here2\n");
			print_error(ERR_MS, cmd->command, ERR_CMD, 0);
			ms_exit(FATAL, E_CODE_CMD_NFOUND);
		}
	}
	printf("2\n");
	validate_executable(cmd);
	printf("3\n");
}
