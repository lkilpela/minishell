/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:32:49 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 05:33:28 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(count, size);
	if (!alloc)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal(alloc);
	return (alloc);
}

char	*ft_safe_strdup(const char *s1)
{
	char	*str;

	str = ft_strdup(s1);
	if (!str)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_strndup(const char *s1, size_t len)
{
	char	*str;

	str = ft_strndup(s1, len);
	if (!str)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	str = ft_substr(s, start, len);
	if (!str)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_itoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)str);
	return (str);
}
