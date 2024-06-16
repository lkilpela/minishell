/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/06/16 07:13:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	error_ret(char *msg)
{
	print_error(ERR_MS, "cd", msg, 0);
	ms()->exit = EXIT_FAILURE;
}

static void	update_pwd(char *added)
{
	char		*old_pwd;
	char		*new_pwd;
	char		*pwd_var;
	char		*tmp;

	pwd_var = lookup_var("PWD");
	ft_free((void **)&ms()->oldpwd);
	ms()->oldpwd = ms()->pwd;
	ms()->pwd = safe_getcwd();
	if (!ms()->pwd)
	{
		print_error(ERR_CD1, "getcwd", ERR_CD2, 1);
		tmp = ft_safe_strjoin("/", added);
		ms()->pwd = ft_safe_strjoin(ms()->oldpwd, tmp);
		ft_free((void **)&tmp);
	}
	new_pwd = ft_safe_strjoin("PWD=", ms()->pwd);
	old_pwd = ft_safe_strjoin("OLDPWD=", pwd_var);
	ft_free((void **)&pwd_var);
	add_var(new_pwd, 1);
	add_var(old_pwd, 1);
	ft_free((void **)&new_pwd);
	ft_free((void **)&old_pwd);
}

void	built_cd(t_cmd *cmd)
{
	char	*home;

	if (cmd->num_of_args == 1)
	{
		home = lookup_var("HOME");
		if (*home == 0)
			return (error_ret(ERR_CD_HOME));
		if (chdir(home) == 0)
		{
			update_pwd(NULL);
			ft_free((void **)&home);
		}
	}
	if (cmd->num_of_args >= 2)
	{
		if (chdir(cmd->args[1]) != 0)
		{
			print_error("minishell: cd", cmd->args[1], NULL, 1);
			ms()->exit = EXIT_FAILURE;
			return ;
		}
		update_pwd(cmd->args[1]);
	}
	ms()->exit = EXIT_SUCCESS;
}
