/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:06:24 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 10:30:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_flag(char *arg)
{
	return (ft_strcmp(arg, "-n") == 0);
}

void	built_echo(t_cmd *cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	while (i < cmd->num_of_args && check_flag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < cmd->num_of_args)
	{
		printf("%s", cmd->args[i++]);
		if (cmd->num_of_args != i)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	ms()->exit = EXIT_SUCCESS;
}
