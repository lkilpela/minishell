/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:49:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/04/12 22:15:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	setup_pipe(t_pipex *p)
{
	if (pipe(p->pipefd) == -1)
		error(ERR_PIPE);
}

//system("leaks pipex");
int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		status;

	init_pipex(argc, argv, envp, &p);
	validate_arguments(&p);
	setup_pipe(&p);
	status = execute_commands(&p);
	if (status != 0)
	{
		cleanup(&p);
		return (status);
	}
	close_all_fds(&p);
	cleanup(&p);
	return (0);
}
