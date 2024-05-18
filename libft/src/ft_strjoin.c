/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:01:24 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 02:37:03 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	len1;
	char	*new_string;

	len1 = ft_strlen(s1) + 1;
	total_len = len1 + ft_strlen(s2);
	new_string = malloc(total_len * sizeof(char));
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1, len1);
	ft_strlcat(new_string, s2, total_len);
	return (new_string);
}
