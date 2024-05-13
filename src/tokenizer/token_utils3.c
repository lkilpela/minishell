/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:46:24 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:47:55 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str) && !is_operator(*str)
		&& !is_quote(*str))
		str++;
	return (str);
}

char	*skip_op(char *str)
{
	if (is_operator(*str))
		str++;
	return (str);
}

char	*skip_quote(char *str)
{
	int	in_quote;

	in_quote = 1;
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
