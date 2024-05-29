/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:22:07 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 15:19:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int	parent(t_commands *c, int i)
{
	while (i < c->num_of_cmds)
	{
		ms()->pid = waitpid(ms()->pids[i], &ms()->status, 0);
		if (ms()->pid == -1)
			ft_error(FATAL, ERR_WAITPID, 1);
		if (WIFEXITED(ms()->status))
			ms()->exit = WEXITSTATUS(ms()->status);
		i++;
	}
	return (0);
}*/
