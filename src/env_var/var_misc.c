/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:38:32 by aklein            #+#    #+#             */
/*   Updated: 2024/06/11 04:23:19 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	shlvl(void)
{
	int		next_shlvl;
	char	*next_level;
	char	*shlvl;
	char	*tmp;

	shlvl = lookup_var("SHLVL");
	if (!str_is_number(shlvl))
		next_shlvl = 0;
	else
		next_shlvl = ft_atoi(shlvl);
	if (next_shlvl < 0)
		next_shlvl = -1;
	next_shlvl++;
	tmp = ft_safe_itoa(next_shlvl);
	next_level = ft_safe_strjoin("SHLVL=", tmp);
	ft_free((void **)&tmp);
	add_var(next_level, 0);
}

int	local_var(t_cmd *cmd, char *str)
{
	if (str && ft_strchr(str, EQUAL_SIGN))
	{
		cmd->args = ft_safe_calloc(1, sizeof(char *));
		cmd->num_of_args = 1;
		cmd->command = ft_safe_strdup("=");
		return (1);
	}
	return (0);
}

void	local_variables(void)
{
	t_list	*locals;
	t_list	*tmp;
	t_cmd	*cmd;

	locals = ms()->local_var_assign;
	while (locals)
	{
		cmd = (t_cmd *)locals->content;
		if (cmd->num_of_args > 1)
			return ;
		if (ms()->cmds_num == 1)
			add_var(cmd->args[0], 1);
		tmp = locals->next;
		ft_free((void **)&locals);
		locals = tmp;
	}
	ms()->local_var_assign = NULL;
}
