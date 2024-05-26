/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/26 21:46:06 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_minishell(int argc, char **argv, char **envp)
{
	init_signals();
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = NULL; //location to store our envp for child processes later
	ms()->paths = NULL;
	ms()->exit = 0;
	ms()->executable = ft_strrchr(argv[0], '/') + 1;	
	get_envp(envp);
	
}

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}
