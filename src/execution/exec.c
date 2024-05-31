/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/31 12:36:33 by codespace        ###   ########.fr       */
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
	dup2(in, STDIN_FILENO);
	if (in != STDIN_FILENO)
		close(in);
	dup2(out, STDOUT_FILENO);
	if (out != STDOUT_FILENO)
		close(out);
}

int	exec_command(t_cmd *cmd)
{
	cmd->exec_path = find_executable(cmd);
	if (cmd->exec_path == NULL)
	{
		print_error(cmd->command, NULL, ERR_CMD, 0);
		exit(EXIT_FAILURE);
	}
	execve(cmd->exec_path, cmd->args, ms()->envp);
	print_error(cmd->command, NULL, NULL, 1);
    exit(EXIT_FAILURE);
}

int	execute_commands(t_list *cmds)
{
	int		status;
	t_cmd	*cmd;
	int		pipe_in;
	int		pid;

	pipe_in = -1;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		validate_redir(&cmd->in_file, &cmd->out_file);
		if (cmds->next != NULL)
		{
			if (pipe(ms()->pipefd) == -1)
				ft_error(FATAL, NULL, 1);	
		}
		pid = fork();
		if (pid == -1)
			ft_error(FATAL, NULL, 1);
		if (pid == 0) //child
		{
			if (pipe_in != -1) //not first
			{
				dup2(pipe_in, STDIN_FILENO);
				close(pipe_in);
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
		else
		{
			if (pipe_in != -1)
				close(pipe_in);
			if (cmds->next != NULL)
			{
				close(ms()->pipefd[P_WRITE]);
				pipe_in = ms()->pipefd[P_READ];
			}
			if (cmd->in_file.fd != -1)
				close(cmd->in_file.fd);
			if (cmd->out_file.fd != -1)
				close(cmd->out_file.fd);
			waitpid(pid, &status, 0);
		}
		cmds = cmds->next;
		
	}
	return (status);
}
