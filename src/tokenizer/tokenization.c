/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:47 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/25 03:06:50 by aklein           ###   ########.fr       */
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
	print_tokens(new_token);
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
	ft_free((void **)&tmp);
	return (next);
}

static int has_closed_quote(char *value)
{
	int	inquote;
	int has_closed_quote;

	inquote = 0;
	has_closed_quote = 0;
	while (*value)
	{
		if (is_quote(*value))
		{
			if (inquote == 0)
				inquote = 1;
			else
			{
				inquote = 0;
				has_closed_quote = 1;
			}
		}
		value++;
	}
	return (has_closed_quote);
}

static int has_one_word(char *value)
{
	while (*value)
	{
		if (*value == ' ')
			return (0);
		value++;
	}
	return (1);
}

t_token_list	*retokenizer(t_token_list **t)
{
	t_token_list	*prev;
	t_token_list	*tmp;

	prev = NULL;
	tmp = *t;
	while (tmp)
	{
		if (!has_closed_quote(tmp->token->value)
			&& !has_one_word(tmp->token->value))
		{
			printf(GREEN "Calling REtokenizer: \n" RESET);
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
