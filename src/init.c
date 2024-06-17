/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/17 12:50:23 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_minishell(int argc, char **argv, char **envp)
{
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = NULL;
	ms()->paths = NULL;
	ms()->exit = 0;
	ms()->executable = ft_strrchr(argv[0], '/') + 1;
	ms()->pwd = safe_getcwd();
	if (!var_declared("PWD"))
		add_var(ft_safe_strjoin("PWD=", ms()->pwd), 0);
	if (!var_declared("OLDPWD"))
		add_var("OLDPWD", 0);
	get_envp(envp);
	init_builtins();
	shlvl();
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
	cmd->out_file.key = NULL;
	cmd->in_file.key = NULL;
	get_all_redir(tokens, cmd);
	return (cmd);
}

t_list	**allocs(void)
{
	static t_list	*allocs = NULL;

	return (&allocs);
}
