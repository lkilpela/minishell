/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 02:29:18 by aklein            #+#    #+#             */
/*   Updated: 2024/06/10 03:04:02 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	set_up_tail(t_token_list *add, t_token_list *index)
{
	while (add->next)
		add = add->next;
	add->next = index->next;
	if (index->next)
		index->next->prev = add;
}

void	list_to_list(t_token_list **lst, t_token_list *add,
				t_token_list **index)
{
	if (!add)
	{
		if ((*index)->prev)
			(*index)->prev->next = (*index)->next;
		if ((*index)->next)
			(*index)->next->prev = (*index)->prev;
		if (*lst == *index)
			*lst = (*index)->next;
		else if (*index != NULL)
			*index = (*index)->next;
	}
	else
	{
		set_up_tail(add, *index);
		if (*lst == *index)
			*lst = add;
		if ((*index)->prev)
		{
			(*index)->prev->next = add;
			add->prev = (*index)->prev;
		}
		*index = add;
	}
}
