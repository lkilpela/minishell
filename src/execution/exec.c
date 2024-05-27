/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 12:49:29 by lkilpela         ###   ########.fr       */
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



/*void execute_cmds(t_commands *cmd, t_execution	*exec)
{
	exec = ft_safe_calloc(1, sizeof(t_execution));
	exec->pids = ft_safe_calloc(cmd->num_of_cmds, sizeof(pid_t));
	exec->pipefds = ft_safe_calloc(cmd->num_of_cmds - 1, sizeof(int[2]));
	
	
}*/
