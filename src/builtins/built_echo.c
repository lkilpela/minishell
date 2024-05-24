/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:06:24 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 14:47:58 by lkilpela         ###   ########.fr       */
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
		printf("echo output: \n");
		printf("%s", cmd->args[i++]);
		if (cmd->num_of_args != i)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}
