/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:15:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/16 21:34:15 by aklein           ###   ########.fr       */
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
	return ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<'));
}

// int is_word(char c)
// {
// 	return ((ft_isalnum(c) || c == '_' || c == '$' || is_quote(c)) && !is_whitespace(c)
// 			&& !is_operator(c));
// }

int is_word(char c)
{
	return (!is_whitespace(c) && !is_operator(c));
}
