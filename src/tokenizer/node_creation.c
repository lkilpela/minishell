/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 03:54:29 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_up_tail(t_token_list **add, t_token_list *index)
{
	t_token_list	*_add;

	_add = *add;
	while (_add->next)
		_add = _add->next;
	_add->next = index->next;
	if (index->next)
		index->next->prev = _add;
}

void	list_to_list(t_token_list **lst, t_token_list *add, t_token_list *index)
{
	set_up_tail(&add, index);
	if (index->prev)
	{
		index->prev->next = add;
		add->prev = index->prev;
	}
	else
	{
		*lst = add;
		add->prev = NULL;
	}
	ft_free((void **)&index->value);
	ft_free((void **)&index);
}

int	var_at_start(char *var, char *start)
{
	if (start == var)
		return (1);
	if (*start == '"' && start + 1 == var)
		return (1);
	return (0);
}

int	var_at_end(char *var)
{
	char	*skip_var;

	skip_var = skip_variable(var);
	if (*skip_var == 0)
		return (1);
	if (*skip_var == '"' && *(skip_var + 1) == 0)
		return (1);
	return (0);
}

int	contains_space(char *var)
{
	char	quote;

	quote = 0;
	while (*var)
	{
		if (!quote && is_whitespace(*var))
			return (1);
		if (!quote && is_quote(*var))
			quote = *var;
		else if (quote && *var == quote)
			quote = 0;
		var++;
	}
	return (0);
}
//string *start where *var is the location of the first var
//return new string after *var is expanded
char	*get_variable(char *var)
{
	char	*key;
	char	*value;
	char	*end;

	end = skip_variable(var);
	key = ft_safe_strndup(var + 1,  end - var - 1);
	value = lookup_var(key);
	ft_free((void **)&key);
	return (value);	
}
char	*exp_word(char *var, char *start)
{
	char	*new;
	char	*tmp;
	char	*final;
	char	*value;

	tmp = ft_safe_strndup(start, var - start);
	value = get_variable(var);
	new = ft_safe_strjoin(tmp, value);
	ft_free((void **)&tmp);
	ft_free((void **)&value);
	final = ft_safe_strjoin(new, skip_variable(var));
	ft_free((void **)&new);
	return (final);
}

t_token_list	*var_to_tok(char *str_start)
{
	t_quote_type	quote;
	char			*str;
	char			*tmp;

	str = str_start;
	quote = NO_QUOTE;	
	while (*str)
	{
		if (is_quote(*str))
			quote = update_quote_type(quote, *str++);
		if (quote != SINGLE_QUOTE && *str == '$')
		{
			tmp = exp_word(str, str_start);
			str_start = tmp;
			str = skip_variable(str);
		}
		else
			str++;
	}
	return (new_tokenizer(str_start));
}

void	exp_and_insert(t_token_list **lst)
{
	t_token_list	*current;
	t_token_list	*new;

	current = *lst;
	while (current)
	{
		if (current->type == WORD && strchr(current->value, '$'))
		{
			new = var_to_tok(current->value);
			list_to_list(lst, new, current);
		}
		current = current->next;
	}
}
