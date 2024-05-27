/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 13:42:40 by lkilpela         ###   ########.fr       */
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

int	execution(t_execution *e)
{
	int		i; // track index of command
	pid_t	pid;

	i = 0;
	e->pids = ft_safe_calloc(e->cmds->num_of_cmds, sizeof(pid_t));
	while (i < e->cmds->num_of_cmds)
	{
		pid = fork();
		if (pid == -1)
			ft_error(FATAL, ERR_FORK, 1);
		if (pid == 0)
		{
			if (i > 0)
				dup2(e->pipefds[i - 1][READ], STDIN_FILENO);
			if (i < e->cmds->num_of_cmds - 1)
				dup2(e->pipefds[i][WRITE], STDOUT_FILENO);
			
			execve(e->cmds->simples[i]->executable, e->cmds->simples[i]->args, ms()->envp);
		}
			
		i++;		
	}
}
