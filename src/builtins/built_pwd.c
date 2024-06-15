/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:17:23 by aklein            #+#    #+#             */
/*   Updated: 2024/06/15 12:47:00 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_pwd(t_cmd *cmds)
{
	char	*pwd;

	(void)cmds;
	pwd = safe_getcwd();
	ft_printf("%s\n", pwd);
	ft_free((void **)&pwd);
	ms()->exit = EXIT_SUCCESS;
}
