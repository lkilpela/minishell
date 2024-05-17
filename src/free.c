/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:51:27 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/17 15:27:53 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>

void	free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}

static void free_var(t_var *var)
{
	if (var)
	{
		free(var->name);
		free(var->value);
		free(var);
	}
}

void free_var_list(t_var_list *list)
{
	t_var_list *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_var(tmp->current_var);
		free(tmp);
	}
}