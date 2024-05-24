/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:16:39 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 19:57:18 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_cd(int argc, char **argv)
{
	char	*home;

	if (argc > 1)
	{
		//error cd: too many arguments
		return ;
	}
	if (argc == 0)
	{
		home = lookup_var("HOME");
		if (*home == 0)
			return ;
			//error $HOME unset
		if (chdir(home) == 0)
			free(home);
	}
	if (argc == 1)
		if (chdir(argv[0]) != 0)
		{
			//error based on errno
			return ;
		}
}
