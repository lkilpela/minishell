/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:35:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 09:48:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	duplicate_fds(t_execution *e)
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

