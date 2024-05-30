/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/30 18:12:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define WRITE 1 // Pipe write_end
#define READ 0 // Pipe read_end

void	setup_pipes(void)
{
	int	i;
	int	num_of_pipes;

	i = 0;
	num_of_pipes = ms()->cmds_num - 1;
	ms()->pipefds = ft_safe_calloc(num_of_pipes, sizeof(int *));
	while (i < num_of_pipes)
	{
		ms()->pipefds[i] = ft_calloc(2, sizeof(int));
		if (pipe(ms()->pipefds[i]) == -1)
			ft_error(FATAL, ERR_PIPE, 1);		
		i++;
	}
}

void	handle_infile(t_redir *infile)
{
	if (infile->file) // if there is an input file for the first command
	{
		if (dup2(infile->fd, STDIN_FILENO) == -1)
		{
			close(infile->fd);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

void	handle_outfile(t_redir *outfile)
{
	if (outfile->file) // if there is an input file for the first command
	{
		if (dup2(outfile->fd, STDOUT_FILENO) == -1)
		{
			close(outfile->fd);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

void	setup_input_dup(int i)
{
	if (i > 0)
	{
		if (dup2(ms()->pipefds[i - 1][READ], STDIN_FILENO) == -1)
		{
			close(ms()->pipefds[i - 1][READ]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

// i: index of command
void	setup_output_dup(int i)
{
	int	num_of_pipes;

	num_of_pipes = ms()->cmds_num - 1;
	
	if (i < num_of_pipes)
	{
		if (dup2(ms()->pipefds[i][WRITE], STDOUT_FILENO) == -1)
		{
			close(ms()->pipefds[i][WRITE]);
			ft_error(FATAL, ERR_DUP2, 1);
		}
	}
}

void	setup_duplication(int i)
{
	setup_input_dup(i);
	setup_output_dup(i);
}

static int	execute_simple_command(t_cmd *cmd)
{
	int		total_args;
	char	**argv;
	int		i;

	i = 0;
	total_args = cmd->num_of_args + 1; // include command itself
	argv = ft_safe_calloc(total_args + 1, sizeof (char *));
	argv[0] = cmd->command;
	while (i < cmd->num_of_args)
	{
		argv[i + 1] = cmd->args[i];
		i++;
	}
	argv[total_args] = NULL;
	cmd->exec_path = find_executable(cmd);
	if (execve(cmd->exec_path, argv, ms()->envp) == -1)
	{
		ft_error(FATAL, ERR_EXECVE, 1);
		free(argv);
		return (-1);
	}
	free(argv);
	return (0);
}

void	close_all_fds(t_list *c, int i)
{
	(void)c;
	(void)i;
	// if (!c)
	// 	return ;
	// if (c->simples[i]->in_file.fd != -1)
	// 	close(c->simples[i]->in_file.fd);
	// if (c->simples[i]->out_file.fd != -1)
	// 	close(c->simples[i]->out_file.fd);
	// if (ms()->pipefds[i][READ] != -1)
	// 	close(ms()->pipefds[i][READ]);
	// if (i != 0 && ms()->pipefds[i][WRITE] != -1)
	// 	close(ms()->pipefds[i][WRITE]);
	return ;
}

int	parent(void)
{
	int	i;

	i = 0;
	while (i < ms()->cmds_num)
	{
		ms()->pid = waitpid(ms()->pids[i], &ms()->status, 0);
		if (ms()->pid == -1)
			ft_error(FATAL, ERR_WAITPID, 1);
		if (WIFEXITED(ms()->status))
			ms()->exit = WEXITSTATUS(ms()->status);
		i++;
	}
	return (0);
}

int	execute_commands(t_list *cmds)
{
	int		i;
	int		has_pipe;
	t_cmd	*cmd;
	
	i = 0;
	has_pipe = ms()->cmds_num > 1;
	if (has_pipe)
		setup_pipes();
	ms()->pids = ft_safe_calloc(ms()->cmds_num, sizeof(pid_t));
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		handle_infile(&cmd->in_file);
		handle_outfile(&cmd->out_file);
		ms()->pids[i] = fork();
		if (ms()->pids[i] == -1)
			ft_error(FATAL, ERR_FORK, 1);
		else if (ms()->pids[i] == 0)
		{
			if (has_pipe)
				setup_duplication(i);
			execute_simple_command(cmd);
			if (has_pipe)
				close_all_fds(cmds, i); //commented out that function
			exit(0);
		}
		i++;
		cmds = cmds->next;
	}
	parent();
	return (0);
}
