/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/07 21:03:41 by aklein           ###   ########.fr       */
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
	init_builtins();
}

t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

t_cmd	*init_cmd(t_token_list *tokens)
{
	t_cmd	*cmd;

	cmd = ft_safe_calloc(1, sizeof(t_cmd));
	cmd->arg_index = 1;
	cmd->in_file.fd = -1;
	cmd->out_file.fd = -1;
	get_all_redir(tokens, cmd);
	return (cmd);
}

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}
