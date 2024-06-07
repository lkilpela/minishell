/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/07 14:50:50 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	extract_var(char *str, char **key, char **value, int *is_set)
{
	char	*equal_sign;

	*key = NULL;
	*value = NULL;
	equal_sign = ft_strchr(str, EQUAL_SIGN);
	if (!equal_sign)
	{
		*key = ft_safe_strdup(str);
		*value = ft_safe_strdup("");
		*is_set = 0;
		return ;
	}
	*key = ft_safe_strndup(str, equal_sign - str);
	if (!*key)
		return ;
	*value = ft_safe_strdup(equal_sign + 1);
	if (!*value)
		return ;
}

// create a new t_var_list node
t_var_list	*create_var_node(char *key, char *value, int is_set)
{
	t_var_list	*node;

	node = ft_safe_calloc(1, sizeof(t_var_list));
	node->key = key;
	node->value = value;
	node->is_set = is_set;
	return (node);
}

static t_var_list	*var_get_last(t_var_list *head)
{
	while (head->next)
		head = head->next;
	return (head);
}

// add new node to the end of list
void	add_var_to_list(t_var_list **head, t_var_list *node)
{
	t_var_list	*last;

	if (*head == NULL)
		*head = node;
	else
	{
		last = var_get_last(*head);
		node->previous = last;
		last->next = node;
	}
}

static void	modify_var(t_var_list *vars, int is_set, 
									char *key, char *value)
{
	if (is_set >= vars->is_set)
	{
		ft_free((void **)&vars->key);
		ft_free((void **)&vars->value);
		vars->key = key;
		vars->value = value;
		vars->is_set = is_set;
	}
}

void	add_var(char *str, int is_local)
{
	t_var_list	*node;
	t_var_list	*vars;
	char		*key;
	char		*value;
	int			is_set;

	is_set = 1;
	extract_var(str, &key, &value, &is_set);
	if (!key || !*key || !value)
		return ;
	vars = ms()->var_list;
	while (vars)
	{
		if (ft_strcmp(vars->key, key) == 0)
		{
			modify_var(vars, is_set, key, value);
			return ;
		}
		vars = vars->next;
	}
	node = create_var_node(key, value, is_set);
	if (is_local)
		node->is_local = 1;
	add_var_to_list(&(ms()->var_list), node);
}
