/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:17:12 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 02:28:45 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*source_cast;
	unsigned char	*destination_cast;

	if ((dest == NULL && src == NULL) || len == 0)
		return (dest);
	if (src < dest)
	{
		source_cast = (unsigned char *)src + len - 1;
		destination_cast = (unsigned char *)dest + len - 1;
		while (len--)
		{
			*destination_cast = *source_cast;
			destination_cast--;
			source_cast--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
