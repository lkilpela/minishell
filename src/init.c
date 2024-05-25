/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/25 03:35:42 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_minishell(int argc, char **argv, char **envp)
{
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = NULL; //location to store our envp for child processes later
	ms()->paths = NULL;
	ms()->executable = ft_strrchr(argv[0], '/') + 1;
	ms()->var_list = get_envp(envp);
}

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}
