/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/06/07 23:52:36 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_ret(char *msg)
{
	print_error(ERR_MS, "cd", msg, 0);
	ms()->exit = EXIT_FAILURE;
}

void	update_pwd(void)
{
	char		*old_pwd;
	char		*last_pwd;
	char		*pwd;
	char		*new_pwd;

	last_pwd = lookup_var("PWD");
	if (last_pwd && *last_pwd != 0)
		last_pwd = ft_safe_strjoin("=", last_pwd);
	old_pwd = ft_safe_strjoin("OLDPWD", last_pwd);
	ft_free((void **)&last_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		print_error("minishell: cd", "getcwd", NULL, 1);
		ms_exit(FATAL, -1);
	}
	pwd = ft_safe_strjoin("PWD=", new_pwd);
	ft_free((void **)&new_pwd);
	add_var(pwd, 1);
	add_var(old_pwd, 1);
	ft_printf("PWD: %s\n", lookup_var("PWD"));
	ft_printf("OLDPWD: %s\n", lookup_var("OLDPWD"));
}

void	built_cd(t_cmd *cmd)
{
	char	*home;
	
	
	if (cmd->num_of_args > 2)
		return (error_ret(ERR_CD_ARGS));
	if (cmd->num_of_args == 1)
	{
		home = lookup_var("HOME");
		if (*home == 0)
			return (error_ret(ERR_CD_HOME));
		if (chdir(home) == 0)
		{
			update_pwd();
			ft_free((void **)&home);
		}
	}
	if (cmd->num_of_args == 2)
	{
		if (chdir(cmd->args[1]) != 0)
		{
			print_error("minishell: cd", cmd->args[1], NULL, 1);
			ms()->exit = EXIT_FAILURE;
			return ;
		}
		update_pwd();
	}
	ms()->exit = EXIT_SUCCESS;
}
