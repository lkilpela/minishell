/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:18:43 by aklein            #+#    #+#             */
/*   Updated: 2024/05/27 00:12:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_key(char *arg)
{
	char	*key;
	char	*value;

	extract_var(arg, &key, &value);
	if (!ft_isalpha(*key) && *key != '_')
		return (0);
	while (*++key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
	}
	return (1);
}

void	built_export(t_simple_cmd *cmd)
{
	int	i;

	i = 0;
	ms()->exit = 0;
	if (cmd->num_of_args == 0)
	{
		built_env(1);
		return ;
	}
	if (cmd->num_of_args >= 1)
	{
		while (i < cmd->num_of_args)
		{
			if (!check_key(cmd->args[i]))
			{
				print_error("bash: export: ", cmd->args[i], ERR_KEY_VALID, 0);
				i++;
				ms()->exit = 1;
				continue ;
			}
			add_var(cmd->args[i]);
			i++;
		}
	}
}
