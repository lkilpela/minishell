/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 08:16:20 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define WRITE 1 // Pipe write_end
#define READ 0 // Pipe read_end

void	setup_pipes(t_execution *e)
{
	int	i;

	i = 0;
	e->pipefds = ft_safe_calloc(e->cmds->num_of_cmds - 1, sizeof(int[2]));
	while (i < e->cmds->num_of_cmds - 1)
	{
		if (pipe(e->pipefds[i]) == -1)
			ft_error(FATAL, ERR_PIPE, 1);
		i++;
	}
}

int	setup_commands(t_execution *e)
{
	int	i;
	t_simple_cmd *cmd;

	i = 0;
	cmd = e->cmds->simples[i];
	while (i < e->cmds->num_of_cmds)
	{
		if (dup2(cmd->in_file.fd, STDIN_FILENO) == -1)
		{
			close(cmd->in_file.fd);
			ft_error(FATAL, ERR_DUP2, 1);
		}
		if (dup2(e->pipefds[i], STDOUT_FILENO) == -1)
		{
			
		}
	}
}



void execute_cmds(t_commands *cmd, t_execution	*exec)
{
	exec = ft_safe_calloc(1, sizeof(t_execution));
	exec->pids = ft_safe_calloc(cmd->num_of_cmds, sizeof(pid_t));
	exec->pipefds = ft_safe_calloc(cmd->num_of_cmds - 1, sizeof(int[2]));
	
	
}
