/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:15:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:39:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_double_operator(char *str)
{
	return (*str == '>' && *(str + 1) == '>') 
		|| (*str == '<' && *(str + 1) == '<');
}

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str) && !is_operator(*str)
		&& !is_quote(*str))
		str++;
	return (str);
}

char *skip_op(char *str)
{
	if (is_operator(*str))
		str++;
	return (str);
}

char *skip_quote(char *str)
{
	int	in_quote = 1;

	str++;
	while (in_quote)
	{
		if (is_quote(*str))
			in_quote = 0;
		else
			str++;
	}
	if (!in_quote)
		str++;
	return (str);
}

char *ft_strndup(char *str, size_t len)
{
	size_t		i;
	char	*dup;

	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

