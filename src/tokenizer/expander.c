/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/17 12:28:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

static char *lookup_var(char *var_name, t_var_list *v)
{
	while (v)
	{
		if (ft_strcmp(v->current_var->name, var_name) == 0)
			return (ft_strdup(v->current_var->value));
		v = v->next;
	}
	return (NULL);
}
// double quotes are removed from string and process expansion
// $HOME $USER -> variables from system environment
char	*expand_env_var(char *str, t_var_list *v)
{
	char	*start;
	char	*end;
	char	*name;
	char	*value;

	start = ft_strchr(str, '$');
	end = skip_variable(start);
	name = ft_strndup(start + 1, end - start - 1);
	value = lookup_var(name, v)
}