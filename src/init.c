/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/22 18:51:03 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_minishell(int argc, char **argv, char **envp)
{
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = NULL; //location to store our envp for child processes later
	ms()->paths = NULL;
	ms()->var_list = get_envp(envp);
}
