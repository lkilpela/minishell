/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:38:41 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 09:06:22 by lkilpela         ###   ########.fr       */
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

void execute_cmds(t_commands *cmd, t_execution	*exec)
{
	exec = ft_safe_calloc(1, sizeof(t_execution));
	exec->pids = ft_safe_calloc(cmd->num_of_cmds, sizeof(pid_t));
	exec->pipefds = ft_safe_calloc(cmd->num_of_cmds - 1, sizeof(int[2]));
	
	
}
