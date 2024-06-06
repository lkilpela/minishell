/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:10 by aklein            #+#    #+#             */
/*   Updated: 2024/06/06 16:16:41 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_env(t_cmd *cmds)
{
	t_var_list	*envs;

	(void)cmds;
	envs = ms()->var_list;
	while (envs)
	{
		if (envs->key && envs->value && envs->is_set)
			ft_printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
	ms()->exit = EXIT_SUCCESS;
}
