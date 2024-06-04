/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 05:23:39 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_minishell(int argc, char **argv, char **envp)
{
	init_signals();
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = NULL;
	ms()->paths = NULL;
	ms()->exit = 0;
	ms()->executable = ft_strrchr(argv[0], '/') + 1;
	get_envp(envp);
}

t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

void	init_redir(t_cmd *cmd)
{
	cmd->in_file.fd = -1;
	cmd->out_file.fd = -1;
}

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}
