/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 17:51:05 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strndup(const char *str, size_t len)
{
	size_t	i;
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

static int	is_var_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// line58: skip dollar sign
// line61-62: skip ? and return the end after the special case
// line64: specific checker for var delimiters which are different from WORD
char	*skip_variable(char *str)
{
	if (*str == '$')
	{
		str++;
		if (*str == '?')
		{
			str++;
			return (str);
		}
		while (*str && is_var_name(*str))
			str++;
	}
	return (str);
}
