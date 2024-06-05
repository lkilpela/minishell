/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 21:26:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
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
	size_t	str_len;
	char	*dup;

	i = 0;
	str_len = ft_strlen(str);
	if (len > str_len)
		len = str_len;
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

char	*skip_variable(char *str)
{
	if (*str == '$')
	{
		str++;
		if (ft_isdigit(*str) || *str == '?')
			return (str + 1);
		if (!ft_isalnum(*str) && *str != '_')
			return (str - 1);
		while (*str && is_var_name(*str))
			str++;
	}
	return (str);
}
