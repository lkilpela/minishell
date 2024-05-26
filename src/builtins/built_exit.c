/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:19:27 by aklein            #+#    #+#             */
/*   Updated: 2024/05/26 21:40:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    exit_banner(void)
{
	ft_printf("                   __   __     __                            \n");
	ft_printf("                  |  \\ |  \\   |  \\                           \n");
	ft_printf("  ______  __    __ \\▓▓_| ▓▓_   \\▓▓_______   ______           \n");
	ft_printf(" /      \\|  \\  /  \\  \\   ▓▓ \\ |  \\       \\ /      \\          \n");
	ft_printf("|  ▓▓▓▓▓▓\\\\▓▓\\/  ▓▓ ▓▓\\▓▓▓▓▓▓ | ▓▓ ▓▓▓▓▓▓▓\\  ▓▓▓▓▓▓\\         \n");
	ft_printf("| ▓▓    ▓▓ >▓▓  ▓▓| ▓▓ | ▓▓ __| ▓▓ ▓▓  | ▓▓ ▓▓  | ▓▓         \n");
	ft_printf("| ▓▓▓▓▓▓▓▓/  ▓▓▓▓\\| ▓▓ | ▓▓|  \\ ▓▓ ▓▓  | ▓▓ ▓▓__| ▓▓__ __ __ \n");
	ft_printf(" \\▓▓     \\  ▓▓ \\▓▓\\ ▓▓  \\▓▓  ▓▓ ▓▓ ▓▓  | ▓▓\\▓▓    ▓▓  \\  \\  \\ \n");
	ft_printf("  \\▓▓▓▓▓▓▓\\▓▓   \\▓▓\\▓▓   \\▓▓▓▓ \\▓▓\\▓▓   \\▓▓_\\▓▓▓▓▓▓▓\\▓▓\\▓▓\\▓▓\n");
	ft_printf("                                          |  \\__| ▓▓         \n");
	ft_printf("                                           \\▓▓    ▓▓         \n");
	ft_printf("                                            \\▓▓▓▓▓▓          \n");
}

int str_is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

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

int	non_numeric_exit(char *arg)
{
	if (!str_is_number(arg))
		return (0);
	if (*arg == '-')
		return (neg_limit(arg));
	return (pos_limit(arg));
}

void	built_exit(t_simple_cmd *cmd)
{
	uint8_t	exit_code;

	exit_banner();
	if (cmd->num_of_args > 1)
	{
		print_error("bash: exit", NULL, "too many arguments", 0);
		return ;
	}
	if (!non_numeric_exit(cmd->args[0]))
	{
		print_error("bash: exit", cmd->args[0], "numeric argument required", 0);
		exit_code = 2;
	}
	else
		exit_code = (uint8_t)ft_atoi(cmd->args[0]);
	clear_lal();
	exit(exit_code);
}
