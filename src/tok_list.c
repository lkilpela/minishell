/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:16 by aklein            #+#    #+#             */
/*   Updated: 2024/05/09 15:35:23 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tok_list	*tok_lstlast(t_tok_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	tok_lstadd_back(t_tok_list **lst, char *str, t_tok type)
{
	t_tok_list	*temp;

	if (!*lst)
	{
		*lst = ft_calloc(1, sizeof(t_tok_list)); //errorcheck
		(*lst)->str = str;
		(*lst)->type = type;
	}
	else
	{
		temp = tok_lstlast(*lst);
		temp->next = ft_calloc(1, sizeof(t_tok_list)); //errorcheck
		temp->next->str = str;
		temp->next->type = type;
	}
}
