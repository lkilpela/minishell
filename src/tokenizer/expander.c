/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/17 21:31:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void	process_var_assigment(char *input, t_var_list *v)
{
	char	*equal_pos;
	char	*temp;
	char	*expanded;

	equal_pos = ft_strchr(input, '=');
	if (equal_pos)
	{
		if (ft_strchr(equal_pos, '$'))
		{
			temp = expand_variable(equal_pos + 1, v);
			expanded = ft_strndup(temp, equal_pos + 1);
			add_var(&v, expanded);
			free(temp);
		}
	}
	else
		add_var(&v, input);
}

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

char	*expand_variable(char *str, t_var_list *v)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	printf("input: %s\n", str);
	start = ft_strchr(str, '$');
	end = skip_variable(start);
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	printf("var_name: %s\n", var_name);
	var_value = lookup_var(var_name, v);
	printf("var_value: %s\n",var_value);
	if (var_value)
	{
		temp = ft_strjoin(prefix, var_value);
		expanded_str = ft_strjoin(temp, end);
		free(temp);
	}
	else	
		expanded_str = ft_strdup(str);
	free(prefix);
	return (expanded_str);
}
