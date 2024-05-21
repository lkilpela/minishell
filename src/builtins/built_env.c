/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:10 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 01:13:08 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_env(void)
{
	char	**envp;
	int		i;

	envp = ms()->envp;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i++], 1);
	}
	return ;
}