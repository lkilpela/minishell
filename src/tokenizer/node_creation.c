/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 14:24:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_list	*create_token_node(char *str)
{
	t_token_list	*node;

	node = ft_calloc(1, sizeof(t_token_list));
	if (!node)
		return (NULL);
	node->token = create_token(str);
	if (!node->token)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

// add a node to a list
static void	add_token_to_list(t_token_list **lst, t_token_list *node)
{
	t_token_list	*last;

	if (*lst == NULL)
		*lst = node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

void	add_token(t_token_list **lst, char *str)
{
	t_token_list	*node;

	node = create_token_node(str);
	if (!node)
		return ;
	add_token_to_list(lst, node);
}
