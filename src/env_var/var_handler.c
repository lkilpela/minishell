/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:33:55 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/10 01:37:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_var_list	*get_envp(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		add_var(envp[i], 0);
		i++;
	}
	return (ms()->var_list);
}

char	*lookup_var(char *key)
{
	t_var_list	*v;

	v = ms()->var_list;
	if (*key == '?')
		return (ft_safe_itoa(ms()->exit));
	while (v)
	{
		if (ft_strcmp(v->key, key) == 0)
			return (ft_safe_strdup(v->value));
		v = v->next;
	}
	return (ft_safe_strdup(""));
}

int	var_declared(char *key)
{
	t_var_list	*vars;

	vars = ms()->var_list;
	while (vars)
	{
		if (ft_strcmp(vars->key, key) == 0)
			return (1);
		vars = vars->next;
	}
	return (0);
}

static int	vars_length(t_var_list *vars)
{
	int	len;

	len = 0;
	while (vars)
	{
		if (!vars->is_local)
			len++;
		vars = vars->next;
	}
	return (len);
}

char	**build_envp()
{
	t_var_list	*vars;
	char		**envs;
	char		*tmp;
	int			i;

	vars = ms()->var_list;
	envs = ft_safe_calloc(vars_length(vars) + 1, sizeof(char *));
	i = 0;
	while (vars)
	{
		if (!vars->is_local)
		{
			tmp = ft_safe_strjoin(vars->key, "=");
			envs[i++] = ft_safe_strjoin(tmp, vars->value);
			ft_free((void **)&tmp);
		}
		vars = vars->next;
	}
	return (envs);
}
