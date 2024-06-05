/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 01:50:07 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 12:43:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	split_list(t_var_list *head, t_var_list **front, t_var_list **back)
{
	t_var_list	*fast;
	t_var_list	*slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		{
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
	}
	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

static t_var_list	*merge_sorted_list(t_var_list *a, t_var_list *b)
{
	t_var_list	*result;

	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (ft_strcmp(a->key, b->key) <= 0)
	{
		result = a;
		result->next = merge_sorted_list(a->next, b);
		result->next->previous = result;
		result->previous = NULL;
	}
	else
	{
		result = b;
		result->next = merge_sorted_list(a, b->next);
		result->next->previous = result;
		result->previous = NULL;
	}
	return (result);
}

void	merge_sort(t_var_list **vars)
{
	t_var_list	*head;
	t_var_list	*a;
	t_var_list	*b;

	head = *vars;
	if (head == NULL || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*vars = merge_sorted_list(a, b);
}
