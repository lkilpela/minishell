/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:53:33 by aklein            #+#    #+#             */
/*   Updated: 2024/06/10 03:05:03 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// create a new t_var_list node
t_var_list	*create_var_node(char *key, char *value, int is_set, int is_local)
{
	t_var_list	*node;

	node = ft_safe_calloc(1, sizeof(t_var_list));
	node->key = key;
	node->value = value;
	node->is_set = is_set;
	node->is_local = is_local;
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
