/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/05/24 23:22:07 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_cd(int argc, char **argv)
{
	char	*home;

	if (argc > 1)
	{
		ft_error(WARNING, "minishell: cd: too many arguments", 0);
		return ;
	}
	if (argc == 0)
	{
		home = lookup_var("HOME");
		if (*home == 0)
		{
			ft_error(WARNING, "minishell: cd: HOME not set", 0);
			return ;
		}
		if (chdir(home) == 0)
			free(home);
	}
	if (argc == 1)
		if (chdir(argv[0]) != 0)
		{
			perror("minishell: cd");
			return ;
		}
}
