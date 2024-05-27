/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 15:24:00 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	wait(t_execution *e, int i)
{
	while (i < e->cmds->num_of_cmds)
	{
		e->pid = waitpid(e->pids[i], &e->status, 0);
		if (e->pid == -1)
			ft_error(FATAL, ERR_WAITPID, 1);
		if (WIFEXITED(e->status))
			ms()->exit = WEXITSTATUS(e->status);
		i++;
	}
}
