/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 19:53:36 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_up_tail(t_token_list *add, t_token_list *index)
{
	while (add->next)
		add = add->next;
	add->next = index->next;
	if (index->next)
		index->next->prev = add;
}

void	list_to_list(t_token_list **lst, t_token_list *add, t_token_list *index)
{
	set_up_tail(add, index);
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
char	*exp_next_var(char *var, char **start)
{
	char	*new;
	char	*beginning;
	char	*final;
	char	*value;
	int		ret_index;

	beginning = ft_safe_strndup(*start, var - *start);
	value = get_variable(var);
	new = ft_safe_strjoin(beginning, value);
	ret_index = ft_strlen(new);
	ft_free((void **)&beginning);
	ft_free((void **)&value);
	final = ft_safe_strjoin(new, skip_variable(var));
	ft_free((void **)&new);
	*start = final;
	return (*start + ret_index);
}

t_token_list	*exp_word(char *str_start)
{
	t_quote_type	quote;
	char			*str;

	str = str_start;
	quote = NO_QUOTE;	
	while (*str)
	{
		quote = update_quote_type(quote, *str);
		if (quote != SINGLE_QUOTE && *str == '$')
			str = exp_next_var(str, &str_start);
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
			new = exp_word(current->value);
			list_to_list(lst, new, current);
		}
		current = current->next;
	}
}
