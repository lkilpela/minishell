/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:53:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/13 14:08:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipex(int argc, char **argv, char **envp, t_pipex *p)
{
	p->argc = argc;
	p->argv = argv;
	p->envp = envp;
	p->infilefd = -1;
	p->outfilefd = -1;
	p->paths = NULL;
	p->cmds[0].path = NULL;
	p->cmds[0].args = NULL;
	p->cmds[1].path = NULL;
	p->cmds[1].args = NULL;
	p->pids[0] = -1;
	p->pids[1] = -1;
	p->pipefd[0] = -1;
	p->pipefd[1] = -1;
	p->wstatus = 0;
	p->ecode = ERR_NONE;
	p->exec_status = 0;
	p->pid = 0;
	
}

void	init_tokenize(t_tokenize *t)
{
	t->count = 0;
	t->in_quotes = 0;
	t->args = NULL;
}
