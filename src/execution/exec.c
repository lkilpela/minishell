/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 15:13:50 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define WRITE 1 // Pipe write_end
#define READ 0 // Pipe read_end

void	setup_pipes(t_execution *e)
{
	int	i;
	int	num_of_pipes;

	i = 0;
	num_of_pipes = e->cmds->num_of_cmds - 1;
	e->pipefds = ft_safe_calloc(num_of_pipes, sizeof(int *));
	while (i < num_of_pipes)
	{
		e->pipefds[i] = ft_calloc(2, sizeof(int));
		pipe(e->pipefds[i]);
		i++;
	}
}

// i: index of command
int	setup_duplication(t_execution *e, int i)
{
	int	num_of_pipes;

	num_of_pipes = e->cmds->num_of_cmds - 1;
	if (i > 0)
	{
		if (dup2(e->pipefds[i - 1][READ], STDIN_FILENO) == -1)
		{
			close(e->pipefds[i - 1][WRITE]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	if (i < num_of_pipes)
	{
		if (dup2(e->pipefds[i][WRITE], STDOUT_FILENO) == -1)
		{
			close(e->pipefds[i][READ]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	return (0);
}

int	execute_simple_command(t_execution *e, int i)
{
	if (execve(e->cmds->simples[i]->executable,
			e->cmds->simples[i]->args, ms()->envp) == -1)
	{
		ft_error(FATAL,ERR_EXECVE, 1);
		return (-1);
	}
	return (0);
}

int	execute_commands(t_execution *e)
{
	int		i; // track index of command

	i = 0;
	e->pids = ft_safe_calloc(e->cmds->num_of_cmds, sizeof(pid_t));
	while (i < e->cmds->num_of_cmds)
	{
		e->pids[i] = fork();
		if (e->pids[i] == -1)
		{
			ft_error(FATAL, ERR_FORK, 1);
			ms()->exit = 1;
		}
		if (e->pids[i] == 0)
		{
			setup_duplication(e, i);
			execute_command(e, i);
			close_all_fds(e, i);
			ms()->exit = 0;
		}
		i++;		
	}
	return (0);
}

void	close_all_fds(t_execution *e, int i)
{
	if (!e)
		return ;
	if (e->cmds->simples[i]->in_file.fd != -1)
		close(e->cmds->simples[i]->in_file.fd);
	if (e->cmds->simples[i]->out_file.fd != -1)
		close(e->cmds->simples[i]->out_file.fd);
	if (e->pipefds[i][READ] != -1)
		close(e->pipefds[i][READ]);
	if (e->pipefds[i][WRITE] != -1)
		close(e->pipefds[i][WRITE]);
}

int	wait(t_execution *e)
{
	int	i;

	while (i < e->cmds->num_of_cmds)
	{
		e->pid = waitpid(e->pids[i], &e->wstatus, 0);
		if (e->pid == -1)
			ft_error(FATAL, ERR_WAITPID, 1);
		if (WIFEXITED(e->exec_status))
			ms()->exit = WEXITSTATUS(e->exec_status);
		i++;
	}
}