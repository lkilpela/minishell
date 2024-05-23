/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 12:22:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void extract_var(char *str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, EQUAL_SIGN);
	if (!equal_sign)
		return ;
	*name = ft_strndup(str, equal_sign - str);
	if (!*name)
		return ;
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
		return ;
}

// create a new t_var_list node
static t_var_list *create_var_node(char *key, char *value)
{
	t_var_list	*node;
	
	node = ft_calloc(1, sizeof(t_var_list));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	return (node);
}

// add new node to the end of list
static void	add_var_to_list(t_var_list *node)
{
	t_var_list	*last;
	
	if (ms()->var_list == NULL)
		ms()->var_list = node;
	else
	{
		last = ms()->var_list;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

void	add_var(char *str)
{
	t_var_list	*node;
	t_var_list	*v;
	char		*key;
	char		*value;

	extract_var(str, &key, &value);
	if (!key || !value)
		return ;
	v = ms()->var_list;
	while (v) // if the name is existed, update it with new one
	{
		if(ft_strcmp(v->key, key) == 0)
		{
			free(v->key);
			free(v->value);
			v->key = key;
			v->value = value;
			return ;
		}
		v = v->next;
	}
	node = create_var_node(key, value);
	if (!node)
		return;
	add_var_to_list(node);
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
