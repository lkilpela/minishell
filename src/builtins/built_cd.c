/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/06/07 23:02:25 by aklein           ###   ########.fr       */
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
	char		*pwd;
	t_var_list	*var;

			
	var = ms()->var_list;
	pwd = ft_safe_strdup(lookup_var("PWD"));
	old_pwd = ft_safe_strdup(lookup_var("OLDPWD"));
	if (ft_strcmp(old_pwd, "") == 0)
	{
		ft_free((void **)&old_pwd);
		old_pwd = ft_safe_strjoin("OLDPWD=", pwd);
		add_var(old_pwd, 1);
	}
	while (var)
	{
		if (ft_strcmp(var->key, "PWD") == 0
			&& ft_strcmp(pwd, ms()->current_pwd) != 0)
		{
			ft_free((void **)&var->value);
			var->value = ft_safe_strdup(ms()->current_pwd);
			printf("PWD <%s>\n", var->value);
		}
		
		if (ft_strcmp(var->key, "OLDPWD") == 0)
		{
			ft_free((void **)&var->value);
			var->value = ft_safe_strdup(pwd);
			printf("OLDPWD: <%s>\n", var->value);
		}
		
		var = var->next;
	}
	ft_free((void **)&pwd);
	ft_free((void **)&old_pwd);
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
			ms()->current_pwd = getcwd(NULL, 0);
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
		ms()->current_pwd = getcwd(NULL, 0);
		update_pwd();
	}
	ms()->exit = EXIT_SUCCESS;
}
