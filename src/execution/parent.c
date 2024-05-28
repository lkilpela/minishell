/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 21:42:01 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parent(t_commands *c, int i)
{
	while (i < c->num_of_cmds)
	{
		c->pid = waitpid(c->pids[i], &c->status, 0);
		if (c->pid == -1)
			ft_error(FATAL, ERR_WAITPID, 1);
		if (WIFEXITED(c->status))
			ms()->exit = WEXITSTATUS(c->status);
		i++;
	}
	return (0);
}
