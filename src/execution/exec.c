/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/03 19:46:17 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	dupes(t_cmd *cmd)
{
	int	in;
	int out;

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

void	exec_command(t_cmd *cmd)
{
	if (builtin_cmd(cmd))
		return ;
	//cmd->exec_path = find_executable(cmd);
	if (cmd->exec_path == NULL)
	{
		print_error(cmd->command, NULL, ERR_CMD, 0);
		ms_exit(FATAL, E_CODE_CMD);
	}
	if (execve(cmd->exec_path, cmd->args, ms()->envp) != 0)
	{
		print_error(cmd->command, NULL, NULL, 1);
		ms_exit(FATAL, E_CODE_CMD);
	}
}

void	child(t_list *cmds, int *pipe_in)
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
		*pipe_in = heredoc_pipefd[P_READ];
	}
	if (*pipe_in != -1) //not first or coming from heredoc
	{
		safe_dup2(*pipe_in, STDIN_FILENO);
		safe_close(*pipe_in);
	}
	if (cmds->next != NULL) //not last
	{
		safe_close(ms()->pipefd[P_READ]);
		safe_dup2(ms()->pipefd[P_WRITE], STDOUT_FILENO);
		safe_close(ms()->pipefd[P_WRITE]);
	}
	dupes(cmd);
	exec_command(cmd);
}

void	parent(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)cmds->content;
	safe_close(*pipe_in);
	if (cmds->next != NULL)
	{
		safe_close(ms()->pipefd[P_WRITE]);
		*pipe_in = dup(ms()->pipefd[P_READ]);
		safe_close(ms()->pipefd[P_READ]);
	}
	safe_close(cmd->in_file.fd);
	safe_close(cmd->out_file.fd);
}

int	get_status(int status)
{
	if (WIFSIGNALED(status) != 0)
		return (E_CODE_SIG + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

void	wait_for_children(void)
{
	int	i;
	int	status;
	
	i = 0;
	while (i < ms()->cmds_num)
	{
		waitpid(ms()->pids[i], &status, 0);
		ms()->exit = get_status(status);
		i++;
	}
}

void	execute_commands(t_list *cmds)
{
	int		pipe_in;
	int		i;

	i = 0;
	pipe_in = -1;
	ms()->pids = ft_safe_calloc(ms()->cmds_num, sizeof(pid_t));
	while (cmds)
	{
		if (cmds->next != NULL)
			safe_pipe(ms()->pipefd);
		ms()->pids[i] = safe_fork();
		if (ms()->pids[i] == 0)
			child(cmds, &pipe_in);
		if (ms()->pids[i++] > 0)
			parent(cmds, &pipe_in);
		cmds = cmds->next;
	}
	wait_for_children();
}
