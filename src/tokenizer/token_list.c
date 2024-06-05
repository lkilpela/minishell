/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 08:53:54 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_len(char *str)
{
	char	inquote;
	int		len;

	len = 0;
	inquote = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			if (inquote == 0)
				inquote = *str;
			else if (inquote == *str)
				inquote = 0;
		}
		else if (!inquote)
		{
			if (is_operator(*str) || is_double_operator(str) || !is_word(*str))
			{
				if (len > 0)
					break ;
				if (is_double_operator(str))
					return (2);
				return (1);
			}
		}
		len++;
		str++;
	}
	return (len);
}

static t_token_type	get_token_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (OP_DLESS);
	else if (!ft_strncmp(str, ">>", 2))
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else if (is_word(*str))
		return (WORD);
	else
		return (UNKNOWN);
}

void	extract_token(char *str, char **value, t_token_type *type)
{
	int	len;

	len = token_len(str);
	*value = ft_safe_strndup(str, len);
	*type = get_token_type(str);
}

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
		if (*index != NULL)
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
