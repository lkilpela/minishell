/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:41:17 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/15 08:02:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*join_arguments(t_pipex *p)
{
	static char	combined_args[1024] = "";
	int			i;
	int			pos;

	i = 0;
	pos = 0;
	while (i < p->argc)
	{
		ft_strlcat(combined_args + pos, p->argv[i], 1024 - pos);
		pos += strlen(p->argv[i]);
		if (i < p->argc - 1)
		{
			ft_strlcat(combined_args + pos, " ", 1024 - pos);
			pos++;
		}
		i++;
	}
	return (combined_args);
}

static int	handle_signal(t_pipex *p, int error_printed)
{
	if (error_printed)
		return (ERR_SIG + WTERMSIG(p->wstatus));
	if ((p->wstatus == SIGINT || p->wstatus == SIGQUIT))
		print_error(ERR_SIGQUIT, join_arguments(p));
	else if (p->wstatus == SIGPIPE)
		print_error(ERR_SIGPIPE, join_arguments(p));
	else if (p->wstatus == SIGCHLD)
		print_error(ERR_SIGCHLD, join_arguments(p));
	else if (p->wstatus == SIGSEGV)
		print_error(ERR_SIGSEGV, join_arguments(p));
	else if (p->wstatus == SIGBUS)
		print_error(ERR_SIGBUS, join_arguments(p));
	else if (p->wstatus == SIGKILL)
		print_error(ERR_SIGKILL, join_arguments(p));
	else if (p->wstatus == SIGABRT)
		print_error(ERR_SIGABRT, join_arguments(p));
	else if (p->wstatus == SIGTERM)
		print_error(ERR_SIGTERM, join_arguments(p));
	else
		print_error(ERR_SIGOTHR, join_arguments(p));
	return (ERR_SIG + WTERMSIG(p->wstatus));
}

static int	check_status(t_pipex *p, int error_printed)
{
	if (WIFSIGNALED(p->wstatus) != 0)
		return (handle_signal(p, error_printed));
	else
		return (WEXITSTATUS(p->wstatus));
}

int	execute_commands(t_pipex *p)
{
	int		i;
	int		error_printed;

	i = 0;
	error_printed = 0;
	p->exec_status = execute_first_command(p);
	if (p->exec_status != 0)
		return (p->exec_status);
	p->exec_status = execute_second_command(p);
	if (p->exec_status != 0)
		return (p->exec_status);
	while (i < 2)
	{
		p->pid = waitpid(p->pids[i], &p->wstatus, 0);
		if (p->pid == -1)
			error(ERR_WAITPID);
		p->ecode = check_status(p, error_printed);
		
		if (!error_printed && p->ecode > 0)
			error_printed = 1;
		if (p->ecode > 255)
			p->ecode = 255;
		i++;
	}
	return (0);
}
