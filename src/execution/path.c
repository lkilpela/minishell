/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:16:21 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 08:29:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_envpaths()
{
	if (ft_strcmp(ms()->var_list->key, "PATH") == 0)
		return (ft_split(ms()->var_list->value, ':'));
	else
		return (NULL);
}

char	*find_local_command(t_commands *c)
{
	int	i;

	i = 0;
	while (i < c->num_of_cmds)
	{
		if (!c->simples[i])
			return (NULL);
		else if (ft_strchr(c->simples[i]), '/')
			return (ft_safe_strdup(c->simples[i]));
	}
	
}