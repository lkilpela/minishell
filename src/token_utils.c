/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 22:15:09 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/10 21:46:49 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str))
		str++;
	return (str);
}



/*int	word_length(char *str)
{
	int	i;

	i = 0;
	while (*str && !ft_strchr(TOKENS, *str) && !ft_is_whitespace(*str))
	{
		i++;
		str++;
	}
	return (i);
}*/



