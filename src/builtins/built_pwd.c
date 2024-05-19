/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:17:23 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 14:39:42 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	built_pwd(t_var_list *v)
{
	char	*pwd;

	pwd = lookup_var("PWD", v);
	ft_printf("%s\n", pwd);
	free(pwd);
}