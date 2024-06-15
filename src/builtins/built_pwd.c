/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:17:23 by aklein            #+#    #+#             */
/*   Updated: 2024/06/15 09:42:35 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_pwd(t_cmd *cmds)
{
	char	*pwd;

	(void)cmds;
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
	ms()->exit = EXIT_SUCCESS;
}
