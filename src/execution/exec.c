/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/01 22:56:50 by lkilpela         ###   ########.fr       */
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
		if (dup2(in, STDIN_FILENO) == -1)
			perror("dup2 in");
		close(in);
	}
	if (out != STDOUT_FILENO)
	{
		if (dup2(out, STDOUT_FILENO) == -1)
			perror("dup2 out");
		close(out);
	}
}

void	exec_command(t_cmd *cmd)
{
	cmd->exec_path = find_executable(cmd);
	if (cmd->exec_path == NULL)
	{
		print_error(cmd->command, NULL, ERR_CMD, 0);
		exit(EXIT_FAILURE);
	}
	if (execve(cmd->exec_path, cmd->args, ms()->envp) != 0)
	{
		print_error(cmd->command, NULL, NULL, 1);
		exit(EXIT_FAILURE); //ft_exit or smth
	}
}

void	child(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)cmds->content;
	if (cmd->heredoc)
	{
		write(ms()->pipefd[P_WRITE], cmd->heredoc, ft_strlen(cmd->heredoc));
		close(ms()->pipefd[P_WRITE]);
		if (ms()->pid > 0)
			dup2(ms()->pipefd[P_READ], STDIN_FILENO);
		*pipe_in = ms()->pipefd[P_READ];
	}
	if (*pipe_in != -1) //not first or coming from heredoc
	{
		dup2(*pipe_in, STDIN_FILENO);
		close(*pipe_in);
	}
	if (cmds->next != NULL) //not last
	{
		close(ms()->pipefd[P_READ]);
		dup2(ms()->pipefd[P_WRITE], STDOUT_FILENO);
		close(ms()->pipefd[P_WRITE]);
	}
	dupes(cmd);
	exec_command(cmd);
}

void	parent(t_list *cmds, int *pipe_in)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)cmds->content;
	if (*pipe_in != -1)
		close(*pipe_in);
	if (cmds->next != NULL)
	{
		close(ms()->pipefd[P_WRITE]);
		*pipe_in = ms()->pipefd[P_READ];
	}
	if (cmd->in_file.fd != -1)
		close(cmd->in_file.fd);
	if (cmd->out_file.fd != -1)
		close(cmd->out_file.fd);
}

int	get_status(int status)
{
	if (WIFSIGNALED(status) != 0)
		return (128 + WTERMSIG(status));
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
	t_cmd	*cmd;
	int		pipe_in;
	int		i;

	i = 0;
	pipe_in = -1;
	ms()->pids = ft_safe_calloc(ms()->cmds_num, sizeof(pid_t));
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		if (!validate_redir(&cmd->in_file) || !validate_redir(&cmd->out_file))
		{
			cmds=cmds->next;
			continue;
		}
		if (cmds->next != NULL)
			if (pipe(ms()->pipefd) == -1)
				ft_error(FATAL, NULL, 1);	
		ms()->pids[i] = fork();
		if (ms()->pids[i] == -1)
			ft_error(FATAL, NULL, 1);
		if (ms()->pids[i] == 0)
			child(cmds, &pipe_in);
		if (ms()->pids[i++] > 0)
			parent(cmds, &pipe_in);
		cmds = cmds->next;
	}
	wait_for_children();
}
