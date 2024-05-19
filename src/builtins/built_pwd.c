/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:17:23 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 12:32:07 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <minishell.h>
#include <tokenizer.h>

void	built_pwd(t_var_list *v)
{
	char	*pwd;

	pwd = lookup_var("PWD", v);
	ft_printf("%s\n", pwd);
	free(pwd);
}