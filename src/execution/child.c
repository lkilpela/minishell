/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:02:31 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/06 00:55:15 by aklein           ###   ########.fr       */
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
	{
		safe_dup2(in, STDIN_FILENO);
		safe_close(in);
	}
	if (out != STDOUT_FILENO)
	{
		safe_dup2(out, STDOUT_FILENO);
		safe_close(out);
	}
}

static void	exec_command(t_cmd *cmd)
{
	if (execute_builtin(cmd))
		ms_exit(FATAL, -1);
	if (cmd->exec_path == NULL)
	{
		print_error(cmd->command, NULL, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD_NFOUND);
	}
	if (execve(cmd->exec_path, cmd->args, ms()->envp) != 0)
	{
		print_error(cmd->command, NULL, NULL, 1);
		ms_exit(FATAL, E_CODE_ERRNO + errno);
	}
}

static void	handle_heredoc_fd(t_cmd *cmd, int *pipe_in, int *heredoc_pipefd)
{
	safe_pipe(heredoc_pipefd);
	write(heredoc_pipefd[P_WRITE], cmd->heredoc, ft_strlen(cmd->heredoc));
	safe_close(heredoc_pipefd[P_WRITE]);
	safe_close(*pipe_in);
	*pipe_in = heredoc_pipefd[P_READ];
}

//line 74: not first or coming from heredoc
//line 79: not last
void	child(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	int		heredoc_pipefd[2];

	cmd = (t_cmd *)cmds->content;
	if (!cmd->command)
		ms_exit(FATAL, EXIT_SUCCESS);
	if (!validate_redir_list(cmd))
		ms_exit(FATAL, EXIT_FAILURE);
	validate_command(cmd);
	if (cmd->heredoc)
		handle_heredoc_fd(cmd, pipe_in, heredoc_pipefd);
	if (*pipe_in != -1)
	{
		safe_dup2(*pipe_in, STDIN_FILENO);
		safe_close(*pipe_in);
	}
	if (cmds->next != NULL)
	{
		safe_close(ms()->pipefd[P_READ]);
		safe_dup2(ms()->pipefd[P_WRITE], STDOUT_FILENO);
		safe_close(ms()->pipefd[P_WRITE]);
	}
	dupes(cmd);
	exec_command(cmd);
}
