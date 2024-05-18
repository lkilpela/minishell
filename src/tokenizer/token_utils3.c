/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:46:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 01:48:19 by aklein           ###   ########.fr       */
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

char	*skip_variable(char *str)
{
	if (*str == '$')
	{
		str++; // skip dollar sign
		if (*str == '?')
			str++; // special case for '$?'
		// str = skip_word(str);
		while (*str && is_var_name(*str))
			str++;
	}
	return (str);
}