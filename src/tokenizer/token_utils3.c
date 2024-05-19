/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:46:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 12:14:49 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && (is_word(*str)))
		str++;
	return (str);
}

char	*skip_op(char *str)
{
	if (is_double_operator(str))
		str += 2;
	else if (is_operator(*str))
		str++;
	return (str);
}

char	*skip_quote(char *str)
{
	char	*end;
	char	quote_type;

	quote_type = *str;
	str++;
	end = ft_strchr(str, quote_type);
	if (end == NULL)
		return (NULL);
	return (end + 1);
}

int	is_var_name(char c)
{
	return (!is_whitespace(c) && !is_operator(c)
		&& !is_quote(c) && c != ':');
}

char	*skip_variable(char *str)
{
	if (*str == '$')
	{
		str++; // skip dollar sign
		if (*str == '?')
		{
			str++; // special case for '$?'
			return (str); //return the end after the special case
		}
		while (*str && is_var_name(*str)) //specific checker for variable delimiters which are different from WORD ones
			str++;
	}
	return (str);
}