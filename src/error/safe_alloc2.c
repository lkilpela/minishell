/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:36:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/13 14:36:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_safe_strdup(const char *s1)
{
	char	*str;

	str = ft_strdup(s1);
	if (!str)
		ft_error(EXIT_FAILURE);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_strndup(const char *s1, size_t len)
{
	char	*str;

	str = ft_strndup(s1, len);
	if (!str)
		ft_error(EXIT_FAILURE);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_strjoin(const char *s1, const char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (!str)
		ft_error(EXIT_FAILURE);
	add_to_lal((void *)str);
	return (str);
}

char	*ft_safe_itoa(int n)
{
	char	*str;

	str = ft_itoa(n);
	if (!str)
		ft_error(EXIT_FAILURE);
	add_to_lal((void *)str);
	return (str);
}

void	*ft_safe_lstnew(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error(EXIT_FAILURE);
	add_to_lal((void *)node);
	return (node);
}

char **ft_safe_split(const char *s, char c)
{
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = ft_split(s, c);
	if (!str_arr)
		ft_error(EXIT_FAILURE);
	while (str_arr[i])
	{
		add_to_lal((void *)str_arr[i]);
		i++;
	}
	return (str_arr);
}