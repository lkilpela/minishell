/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:10 by aklein            #+#    #+#             */
/*   Updated: 2024/05/28 16:15:32 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_env(int declare)
{
	t_var_list	*envs;

	envs = ms()->var_list;
	while (envs)
	{
		if (envs->key && envs->value)
		{
			if (declare)
			{
				ft_printf("declare -x ");
				ft_printf("declare -x %s=\"%s\"\n", envs->key, envs->value);
			}
			else
				ft_printf("%s=%s\n", envs->key, envs->value);
		}
		envs = envs->next;
	}
	ms()->exit = 0;
}
