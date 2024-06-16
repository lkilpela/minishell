/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:02:31 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/16 08:29:05 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	dupes(t_cmd *cmd)
{
	int	in;
	int	out;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	if (cmd->in_file.fd != -1)
		in = cmd->in_file.fd;
	if (cmd->out_file.fd != -1)
		out = cmd->out_file.fd;
	if (in != STDIN_FILENO)
		safe_dup2(in, STDIN_FILENO);
	if (out != STDOUT_FILENO)
		safe_dup2(out, STDOUT_FILENO);
}

static void	exec_command(t_cmd *cmd)
{
	if (execute_builtin(cmd))
		ms_exit(FATAL, -1);
	if (cmd->exec_path == NULL)
	{
		if (cmd->null_path)
			print_error(ERR_MS, cmd->command, NULL, 1);
		else
			print_error(cmd->command, NULL, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
	if (execve(cmd->exec_path, cmd->args, build_envp()) != 0)
	{
		print_error(cmd->command, NULL, NULL, 1);
		ms_exit(FATAL, EXIT_FAILURE);
	}
}

static void	handle_heredoc_fd(t_cmd *cmd, int *pipe_in, int *heredoc_pipefd)
{
	char	*heredoc;

	heredoc = cmd->in_file.file;
	safe_pipe(heredoc_pipefd);
	write(heredoc_pipefd[P_WRITE], heredoc, ft_strlen(heredoc));
	safe_close(heredoc_pipefd[P_WRITE]);
	safe_close(*pipe_in);
	*pipe_in = heredoc_pipefd[P_READ];
}

void	child(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	int		heredoc_pipefd[2];

	cmd = (t_cmd *)cmds->content;
	if (!cmd->command)
		ms_exit(FATAL, -1);
	validate_command(cmd);
	if (cmd->in_file.type == HEREDOC)
		handle_heredoc_fd(cmd, pipe_in, heredoc_pipefd);
	if (*pipe_in != -1)
		safe_dup2(*pipe_in, STDIN_FILENO);
	if (cmds->next != NULL)
	{
		safe_close(ms()->pipefd[P_READ]);
		safe_dup2(ms()->pipefd[P_WRITE], STDOUT_FILENO);
	}
	dupes(cmd);
	close_fds();
	exec_command(cmd);
}
