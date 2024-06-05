/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:40:03 by aklein            #+#    #+#             */
/*   Updated: 2024/06/05 18:40:05 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_lstnew(void *content)
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
		ft_error(E_CODE_ERRNO + errno);
	add_to_lal((void *)node);
	return (node);
}
