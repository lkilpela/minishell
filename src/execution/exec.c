/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 21:53:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define WRITE 1 // Pipe write_end
#define READ 0 // Pipe read_end

void	setup_pipes(t_commands *c)
{
	int	i;
	int	num_of_pipes;

	i = 0;
	num_of_pipes = c->num_of_cmds - 1;
	c->pipefds = ft_safe_calloc(num_of_pipes, sizeof(int *));
	while (i < num_of_pipes)
	{
		c->pipefds[i] = ft_calloc(2, sizeof(int));
		pipe(c->pipefds[i]);
		printf("Pipe %d: read end = %d, write end = %d\n", i, c->pipefds[i][0], c->pipefds[i][1]);
		i++;
	}
}

// i: index of command
int	setup_duplication(t_commands *c, int i)
{
	int	num_of_pipes;

	num_of_pipes = c->num_of_cmds - 1;
	if (i > 0)
	{
		if (dup2(c->pipefds[i - 1][READ], STDIN_FILENO) == -1)
		{
			close(c->pipefds[i - 1][WRITE]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	if (i < num_of_pipes)
	{
		if (dup2(c->pipefds[i][WRITE], STDOUT_FILENO) == -1)
		{
			close(c->pipefds[i][READ]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	printf("Command %s: read end = %d, write end = %d\n", c->simples[i]->command, c->pipefds[i][READ], c->pipefds[i][WRITE]);
	return (0);
}

static int	execute_simple_command(t_simple_cmd *s)
{
	if (execve(s->executable, s->args, ms()->envp) == -1)
	{
		ft_error(FATAL, ERR_EXECVE, 1);
		return (-1);
	}
	return (0);
}

void	close_all_fds(t_commands *c, int i)
{
	if (!c)
		return ;
	if (c->simples[i]->in_file.fd != -1)
		close(c->simples[i]->in_file.fd);
	if (c->simples[i]->out_file.fd != -1)
		close(c->simples[i]->out_file.fd);
	if (c->pipefds[i][READ] != -1)
		close(c->pipefds[i][READ]);
	if (c->pipefds[i][WRITE] != -1)
		close(c->pipefds[i][WRITE]);
}

int	execute_commands(t_commands *c)
{
	int	i;

	i = 0;
	c->pids = ft_safe_calloc(c->num_of_cmds, sizeof(pid_t));
	while (i < c->num_of_cmds)
	{
		c->pids[i] = fork();
		if (c->pids[i] == -1)
			ft_error(FATAL, ERR_FORK, 1);
		if (c->pids[i] == 0)
		{
			setup_duplication(c, i);
			execute_simple_command(c->simples[i]);
			close_all_fds(c, i);
		}
		i++;
	}
	return (0);
}
