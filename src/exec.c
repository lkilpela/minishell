/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:34:36 by aklein            #+#    #+#             */
/*   Updated: 2024/05/13 14:54:01 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <unistd.h>

void	child(t_commands *cmds, int i)
{
	int	p_fd[2];

	if (pipe(p_fd) == -1)
		error();
	if (i < cmds->num_of_cmds)
	{
		dup2(cmds->simples[i]->in_file.fd, p_fd[0]);
		dup2(cmds->simples[i]->out_file.fd, p_fd[1]);
	}
}

void	execute(t_commands *cmds)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		child(cmds, 0);
}