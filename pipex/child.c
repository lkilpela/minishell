/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/12 22:12:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//1st child: any reads from STDIN: read from the input file, 
//any writes to STDOUT: write to the pipe.
static int	setup_first_command(t_pipex *p)
{
	if (dup2(p->infilefd, STDIN_FILENO) == -1)
	{
		close(p->infilefd);
		error(ERR_DUP2);
	}
	if (dup2(p->pipefd[1], STDOUT_FILENO) == -1)
	{
		close(p->pipefd[1]);
		close(p->infilefd);
		error(ERR_DUP2);
	}
	return (0);
}

//2nd child: any reads from STDIN: read from the pipe, 
//any writes to STDOUT: write to the output file.
static int	setup_second_command(t_pipex *p)
{
	if (dup2(p->pipefd[0], STDIN_FILENO) == -1)
	{
		close(p->pipefd[0]);
		error(ERR_DUP2);
	}
	if (dup2(p->outfilefd, STDOUT_FILENO) == -1)
	{
		close(p->pipefd[0]);
		close(p->outfilefd);
		error(ERR_DUP2);
	}
	return (0);
}

static int	execute_command( t_pipex *p, t_command *c)
{
	if (execve(c->path, c->args, p->envp) == -1)
	{
		error(ERR_EXECVE);
		return (-1);
	}
	return (0);
}

int	execute_first_command(t_pipex *p)
{
	int	status;

	p->pids[0] = fork();
	if (p->pids[0] == -1)
		error(ERR_FORK);
	else if (p->pids[0] == 0)
	{
		status = setup_first_command(p);
		if (status != 0)
			exit(status);
		status = execute_command(p, &p->cmds[0]);
		if (status != 0)
			exit(status);
	}
	close(p->pipefd[1]);
	return (0);
}

int	execute_second_command(t_pipex *p)
{
	int	status;

	p->pids[1] = fork();
	if (p->pids[1] == -1)
		error(ERR_FORK);
	if (p->pids[1] == 0)
	{
		close(p->pipefd[1]);
		status = setup_second_command(p);
		if (status != 0)
			exit(status);
		status = execute_command(p, &p->cmds[1]);
		if (status != 0)
			exit(status);
	}
	close(p->pipefd[0]);
	return (0);
}
