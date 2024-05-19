/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:16 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 13:51:16 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token_list	*new_node(t_token token)
{
	t_token_list	*lst;

	lst = malloc(sizeof(t_token_list));
	if (!lst)
		return (NULL);
	lst->token = token;
	lst->next = NULL;
	return (lst);
}

static t_token_list	*last_node(t_token_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	append_node(t_token_list **lst, t_token token)
{
	t_token_list	*last;

	if (!*lst)
		*lst = new_node(token);
	else
	{
		last = last_node(*lst);
		last->next = new_node(token);
	}
}

static void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	free(lst->token.value);
	free(lst);
}

void	free_list(t_token_list **lst)
{
	t_token_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		delone_node(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	print_tokens(t_token_list *lst)
{
	t_token_list	*temp;

	temp = lst;
	while (temp) 
	{
		printf("Value: '%s' Type: '%d'\n", temp->token.value, temp->token.type);
		temp = temp->next;
	}
}
