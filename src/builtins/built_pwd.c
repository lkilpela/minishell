/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:17:23 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 08:41:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_pwd(t_cmd *cmds)
{
	char	*pwd;

	(void)cmds;
	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	ft_free((void **)&pwd);
	ms()->exit = EXIT_SUCCESS;
}
