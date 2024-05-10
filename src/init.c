/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/10 11:06:15 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_minishell(int argc, char **argv, char **envp, t_minishell *m)
{
	m->argc = argc;
	m->argv = argv;
	m->envp = envp;
}