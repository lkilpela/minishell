/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:27 by aklein            #+#    #+#             */
/*   Updated: 2024/06/15 11:20:42 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	neg_limit(char *str)
{
	int	len;

	str++;
	len = ft_strlen(str);
	if (len < 19)
		return (1);
	if (len == 19 && str[len - 1] <= '8')
		return (1);
	return (0);
}

static int	pos_limit(char *str)
{
	int	len;

	if (*str == '+')
		str++;
	len = ft_strlen(str);
	if (len < 19)
		return (1);
	if (len == 19 && str[len - 1] <= '7')
		return (1);
	return (0);
}

static int	non_numeric_exit(char *arg)
{
	if (!str_is_number(arg))
		return (0);
	if (*arg == '-')
		return (neg_limit(arg));
	return (pos_limit(arg));
}

void	built_exit(t_cmd *cmd)
{
	uint8_t	exit_code;

	if (!cmd || cmd->num_of_args == 1)
	{
		// ft_putendl_fd("exit", STDOUT_FILENO);
		ms_exit(FATAL, ms()->exit);
	}
	if (!non_numeric_exit(cmd->args[1]))
	{
		print_error("minishell: exit",
			cmd->args[1], "numeric argument required", 0);
		exit_code = 2;
	}
	else if (cmd->num_of_args > 2)
	{
		print_error("minishell: exit", NULL, "too many arguments", 0);
		ms()->exit = EXIT_FAILURE;
		return ;
	}
	else
		exit_code = (uint8_t)ft_atoi(cmd->args[1]);
	// ft_putendl_fd("exit", STDOUT_FILENO);
	ms_exit(FATAL, exit_code);
}
