/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:18:16 by aklein            #+#    #+#             */
/*   Updated: 2024/05/10 13:23:09 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

t_token_list	*new_node(t_token_list *lst, t_token token)
{
	t_token_list *new;

	new = malloc(sizeof(t_token_list));
	if (!new)
		return (NULL);
	new->token = token;
	new->next = NULL;
	return (new);
}
t_token_list	*last_node(t_token_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_token_list	*add_node(t_token_list **lst, t_token token)
{
	t_token_list	*last;

	if (!lst)
		return (NULL);
	if (!*lst)
		new_node(lst, token);
	else
	{
		last = last_node(*lst);
		new_node(&(last->next), token);
	}
	return (*lst);
}

static void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	free(lst->token.value);
	free(lst);
}

void	clear_list(t_token_list **lst)
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

/*void	tok_lstadd_back(t_token_list **lst, char *str, t_token type)
{
	t_token_list	*temp;

	if (!*lst)
	{
		*lst = ft_calloc(1, sizeof(t_token_list)); //errorcheck
		(*lst)->str = str;
		(*lst)->type = type;
	}
	else
	{
		temp = tok_lstlast(*lst);
		temp->next = ft_calloc(1, sizeof(t_token_list)); //errorcheck
		temp->next->str = str;
		temp->next->type = type;
	}
}*/
