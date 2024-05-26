/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/26 22:07:31 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	extract_var(char *str, char **key, char **value)
{
	char	*equal_sign;

	*key = NULL;
	*value = NULL;
	equal_sign = ft_strchr(str, EQUAL_SIGN);
	if (!equal_sign)
		return ;
	*key = ft_safe_strndup(str, equal_sign - str);
	if (!*key)
		return ;
	*value = ft_safe_strdup(equal_sign + 1);
	if (!*value)
		return ;
}

// create a new t_var_list node
static t_var_list	*create_var_node(char *key, char *value)
{
	t_var_list	*node;

	node = ft_safe_calloc(1, sizeof(t_var_list));
	node->key = key;
	node->value = value;
	return (node);
}

static t_var_list	*var_get_last(void)
{
	t_var_list	*last;

	last = ms()->var_list;
	while (last->next)
		last = last->next;
	return (last);
}

// add new node to the end of list
static void	add_var_to_list(t_var_list *node)
{
	t_var_list	*last;

	if (ms()->var_list == NULL)
		ms()->var_list = node;
	else
	{
		last = var_get_last();
		node->previous = last;
		last->next = node;
	}
}

void	add_var(char *str)
{
	t_var_list	*node;
	t_var_list	*vars;
	char		*key;
	char		*value;

	extract_var(str, &key, &value);
	if (!key || !*key || !value)
		return ;
	vars = ms()->var_list;
	while (vars)
	{
		if (ft_strcmp(vars->key, key) == 0)
		{
			ft_free((void **)&vars->key);
			ft_free((void **)&vars->value);
			vars->key = key;
			vars->value = value;
			return ;
		}
		vars = vars->next;
	}
	node = create_var_node(key, value);
	add_var_to_list(node);
}
