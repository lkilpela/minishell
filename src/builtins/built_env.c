/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:10 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 21:36:33 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	built_env(int declare)
// {
// 	char	**envp;
// 	int		i;

// 	envp = ms()->envp;
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		if (ft_strchr(envp[i], EQUAL_SIGN))
// 		{
// 			if (declare)
// 				ft_putstr_fd("declare -x ", 1);
// 			ft_putendl_fd(envp[i++], 1);
// 		}
// 	}
// 	return ;
// }

void	built_env(int declare)
{
	t_var_list	*envs;

	envs = ms()->var_list;
	while (envs)
	{
		if (envs->key && envs->value)
		{
			if (declare)
				ft_printf("declare -x ");
			ft_printf("%s=%s\n", envs->key, envs->value);
		}
		envs = envs->next;
	}
}