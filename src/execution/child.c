/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:02:31 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 05:02:59 by lkilpela         ###   ########.fr       */
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
	if (builtin_cmd(cmd))
		return ;
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

//line 71: not first or coming from heredoc
//line 76: not last
static void	child(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	int		heredoc_pipefd[2];

	cmd = (t_cmd *)cmds->content;
	validate_command(cmd);
	if (cmd->heredoc)
	{
		safe_pipe(heredoc_pipefd);
		write(heredoc_pipefd[P_WRITE], cmd->heredoc, ft_strlen(cmd->heredoc));
		safe_close(heredoc_pipefd[P_WRITE]);
		safe_close(*pipe_in);
		*pipe_in = heredoc_pipefd[P_READ];
	}
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
