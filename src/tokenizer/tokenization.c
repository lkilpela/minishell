/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 07:46:49 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// converts a string into a list of tokens
t_token_list	*tokenizer(char *str)
{
	t_token_list	*lst;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		add_token(&lst, str);
		str += token_len(str);
	}
	return (lst);
}

static t_token_list	*reprocess_token(t_token_list **t, t_token_list *tmp,
								t_token_list **prev)
{
	t_token_list	*new_token;
	t_token_list	*last_new_token;
	t_token_list	*next;

	new_token = tokenizer(tmp->token->value);
	if (!new_token)
		return (tmp->next);
	last_new_token = new_token;
	while (last_new_token->next)
		last_new_token = last_new_token->next;
	if ((*prev))
		(*prev)->next = new_token;
	else
		*t = new_token;
	last_new_token->next = tmp->next;
	next = tmp->next;
	free(tmp);
	return (next);
}

// ls$ARG hello | echo < output
t_token_list	*retokenizer(t_token_list **t)
{
	t_token_list	*prev;
	t_token_list	*tmp;

	prev = NULL;
	tmp = *t;
	while (tmp)
	{
		if (ft_strchr(tmp->token->value, ' '))
		{
			tmp = reprocess_token(t, tmp, &prev);
			if (!tmp)
				return (NULL);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (*t);
}
