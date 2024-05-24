/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:33:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 11:40:35 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_empty_var_assignment(char **input)
{
	if (*input == NULL || **input == '\0')
	{
		add_var(*input);
		return ;
	}
}

void	process_var_assignment(char **input)
{
	char			*equal_pos;
	char			*value;
	char			*prefix;
	char			*new_input;

	handle_empty_var_assignment(input);
	new_input = NULL;
	equal_pos = ft_strchr(*input, EQUAL_SIGN);
	if (equal_pos)
	{
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		value = check_quotes_and_expand(equal_pos + 1);
		new_input = ft_strjoin(prefix, value);
		if (new_input)
		{
			add_var(new_input);
			free(prefix);
			free(new_input);
		}
	}
	else
		add_var(*input);
	print_last_node();
}

t_var_list	*get_envp(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		add_var(envp[i]);
		i++;
	}
	return (ms()->var_list);
}

void	var_remove(char *key)
{
	t_var_list	*vars;

	vars = ms()->var_list;
	if (!key)
		return ;
	while (vars)
	{
		if (ft_strcmp(key, vars->key) == 0)
		{
			if (vars->previous)
				vars->previous->next = vars->next;
			if (vars->next)
				vars->next->previous = vars->previous;
			free(vars);
			vars = NULL;
			return ;
		}
		vars = vars->next;
	}
}
