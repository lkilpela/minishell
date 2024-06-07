/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/06/07 11:16:59 by lkilpela         ###   ########.fr       */
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
	char	*old_pwd;
	char	*pwd;

	ms()->current_pwd = getcwd(NULL, 0);
	pwd = lookup_var("PWD");
	if (pwd && ft_strcmp(pwd, ms()->current_pwd) != 0)
	{
		old_pwd = lookup_var("OLDPWD");
		if (ft_strcmp(old_pwd, "") == 0)
		{
			old_pwd = ft_safe_strjoin("OLDPWD=", pwd);
			add_var(old_pwd);
			ft_free((void **)&old_pwd);
		}
		ft_free((void **)&pwd);
		pwd = ft_safe_strdup(ms()->current_pwd);
	}
}

void	built_cd(t_cmd *cmd)
{
	char	*home;
	
	//ms()->current_pwd = getcwd(NULL, 0);
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
