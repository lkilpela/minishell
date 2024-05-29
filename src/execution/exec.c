/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 12:04:10 by lkilpela         ###   ########.fr       */
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
	ms()->pipefds = ft_safe_calloc(num_of_pipes, sizeof(int *));
	while (i < num_of_pipes)
	{
		ms()->pipefds[i] = ft_calloc(2, sizeof(int));
		pipe(ms()->pipefds[i]);
		//printf("Pipe %d: read end = %d, write end = %d\n", i, c->pipefds[i][0], c->pipefds[i][1]);
		i++;
	}
}

void	setup_input_dup(t_commands *c, int i)
{
	if (i > 0)
	{
		if (dup2(ms()->pipefds[i - 1][READ], STDIN_FILENO) == -1)
		{
			close(ms()->pipefds[i - 1][READ]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	else if (c->simples[i]->in_file.file || c->simples[i]->heredoc) // if there is an input file for the first command
	{
		if (dup2(c->simples[i]->in_file.fd, STDIN_FILENO) == -1)
		{
			close(c->simples[i]->in_file.fd);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

// i: index of command
void	setup_output_dup(t_commands *c, int i)
{
	int	num_of_pipes;

	num_of_pipes = c->num_of_cmds - 1;
	
	if (i < num_of_pipes)
	{
		if (dup2(ms()->pipefds[i][WRITE], STDOUT_FILENO) == -1)
		{
			close(ms()->pipefds[i][WRITE]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
	else if (c->simples[i]->out_file.file) // if there is an output file for the last command
	{
		if (dup2(c->simples[i]->out_file.fd, STDOUT_FILENO) == -1)
		{
			close(c->simples[i]->out_file.fd);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

void	setup_duplication(t_commands *c, int i)
{
	setup_input_dup(c, i);
	setup_output_dup(c, i);
}

static int	execute_simple_command(t_simple_cmd *s)
{
	int		total_args;
	char	**argv;
	int		i;

	i = 0;
	total_args = s->num_of_args + 1; // include command itself
	argv = ft_safe_calloc(total_args + 1, sizeof (char *));
	argv[0] = s->command;
	while (i < s->num_of_args)
	{
		argv[i + 1] = s->args[i];
		i++;
	}
	argv[total_args] = NULL;
	if (execve(s->exec_path, argv, ms()->envp) == -1)
	{
		ft_error(FATAL, ERR_EXECVE, 1);
		free(argv);
		return (-1);
	}
	free(argv);
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
	if (ms()->pipefds[i][READ] != -1)
		close(ms()->pipefds[i][READ]);
	if (ms()->pipefds[i][WRITE] != -1)
		close(ms()->pipefds[i][WRITE]);
}

int	execute_commands(t_commands *c)
{
	int	i;

	i = 0;
	ms()->pids = ft_safe_calloc(c->num_of_cmds, sizeof(pid_t));
	while (i < c->num_of_cmds)
	{
		ms()->pids[i] = fork();
		if (ms()->pids[i] == -1)
			ft_error(FATAL, ERR_FORK, 1);
		if (ms()->pids[i] == 0)
		{
			setup_duplication(c, i);
			execute_simple_command(c->simples[i]);
			close_all_fds(c, i);
			exit(0);
		}
		i++;
	}
	parent(c, 0);
	return (0);
}
