/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 04:23:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	print_args(t_cmd *cmd)
{
	int	i;
	int	total_len;
	char *args_str;

	i = 0;
	total_len = 0;
	while (i < cmd->num_of_args)
	{
		total_len += ft_strlen(cmd->args[i]);
		i++;
	}
	total_len += cmd->num_of_args - 1 + 1;
	args_str = ft_safe_calloc(total_len, sizeof(char));
	i = 0;
	while (i < cmd->num_of_args)
	{
		ft_strlcat(args_str, cmd->args[i], total_len);
		if (cmd->args[i + 1])
			ft_strlcat(args_str, " ", total_len);
		i++;
	}
	print_error(ERR_MS, args_str, ERR_DIR, 0);
	ft_free((void **)&args_str);
}

void	validate_command(t_cmd *cmd)
{
	if (!validate_redir(&cmd->in_file) || !validate_redir(&cmd->out_file))
		ms_exit(FATAL, E_CODE_FILE);
	if (get_builtin(cmd).name)
		return ;
	cmd->exec_path = find_executable(cmd);
	if (is_directory(cmd))
	{
		print_error(ERR_MS, cmd->command, ERR_DIR, 0);
		ms_exit(FATAL, E_CODE_CMD_NEXEC);
	}
	if (cmd->exec_path != NULL)
	{
		if(access(cmd->exec_path, X_OK) == -1)
		{
			if (errno == ENOENT)
            {
                print_error(ERR_MS, cmd->command, ERR_FILE, 0);
                ms_exit(FATAL, ENOENT);
            }
            else if (errno == EACCES)
            {
                print_error(ERR_MS, cmd->command, ERR_PERM, 0);
                ms_exit(FATAL, EACCES);
            }
		}
	}
	else
	{
		print_error(ERR_MS, cmd->command, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
}
