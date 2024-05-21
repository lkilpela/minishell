/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:06:24 by aklein            #+#    #+#             */
/*   Updated: 2024/05/20 11:10:38 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_flag(char *arg)
{
	if (*arg++ != '-')
		return (0);
	while (*arg)
	{
		if (*arg++ != 'n')
			return (0);
	}
	return (1);
}

void	built_echo(t_simple_cmd *cmd)
{
	int	i;
	int	n_flag;

	if (!cmd || ft_strcmp(cmd->command, "echo") != 0)
		return ;
	i = 0;
	n_flag = 0;
	if (i < cmd->num_of_args && check_flag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < cmd->num_of_args)
	{
		ft_printf("%s", cmd->args[i++]);
		if (cmd->num_of_args != i)
			ft_printf(" ");
	}
	if (!n_flag)
		ft_printf("\n");
}
