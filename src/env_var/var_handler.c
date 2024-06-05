/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:33:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 12:49:49 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			ft_free((void **)&vars);
			vars = NULL;
			return ;
		}
		vars = vars->next;
	}
}

char	*lookup_var(char *var_name)
{
	t_var_list	*v;

	v = ms()->var_list;
	if (*var_name == '?')
		return (ft_safe_itoa(ms()->exit));
	while (v)
	{
		if (ft_strcmp(v->key, var_name) == 0)
			return (ft_safe_strdup(v->value));
		v = v->next;
	}
	return (ft_safe_strdup(""));
}
