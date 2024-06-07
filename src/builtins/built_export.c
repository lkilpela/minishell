/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:18:43 by aklein            #+#    #+#             */
/*   Updated: 2024/06/07 22:02:48 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_key(char *arg)
{
	char	*key;
	char	*value;
	int		is_set;

	is_set = 1;
	extract_var(arg, &key, &value, &is_set);
	if (!key || (!ft_isalpha(*key) && *key != '_'))
		return (0);
	while (*++key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
	}
	return (1);
}

static t_var_list	*duplicate_var_list(t_var_list *vars)
{
	t_var_list	*result;
	t_var_list	*node;

	result = NULL;
	while (vars)
	{
		node = create_var_node(vars->key, vars->value, 
								vars->is_set, vars->is_local);
		add_var_to_list(&result, node);
		vars = vars->next;
	}
	return (result);
}

void	print_sorted_vars(t_var_list *vars)
{
	t_var_list	*dup;
	t_var_list	*tmp;

	dup = duplicate_var_list(vars);
	merge_sort(&dup);
	while (dup)
	{
		if (!dup->is_local)
		{
			if (dup->is_set == 1)
				ft_printf("declare -x %s=\"%s\"\n", dup->key, dup->value);
			else
				ft_printf("declare -x %s\n", dup->key);
		}
		tmp = dup;
		dup = dup->next;
		ft_free((void **)&tmp);
	}
}

int	check_args(int args)
{
	if (args == 1)
	{
		print_sorted_vars(ms()->var_list);
		return (0);
	}
	else
		return (1);
}

void	built_export(t_cmd *cmd)
{
	int		i;

	i = 1;
	ms()->exit = EXIT_SUCCESS;
	if (check_args(cmd->num_of_args))
	{
		while (i < cmd->num_of_args)
		{
			if (!check_key(cmd->args[i]))
			{
				print_error("minishell: export: ",	
							cmd->args[i], ERR_KEY_VALID, 0);
				i++;
				ms()->exit = EXIT_FAILURE;
				continue ;
			}
			add_var(cmd->args[i], 0);
			i++;
		}
	}
}
