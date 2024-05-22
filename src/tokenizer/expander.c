/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/22 19:56:38 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handle_empty_var_assignment(char **input)
{
	if (*input == NULL || **input == '\0')
	{
		add_var(*input);
		return ;
	}
}

void	process_var_assignment(char **input)
{
	char	*equal_pos;
	char	*value;
	char	*prefix;
	char 	*new_input;
	
	handle_empty_var_assignment(input);
	new_input = NULL;
	equal_pos = ft_strchr(*input, EQUAL_SIGN);
	if (equal_pos)
	{
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		value = handle_quotes(equal_pos + 1);
		new_input = ft_strjoin(prefix, value);
		if (new_input)
		{
			add_var( new_input);
			free(prefix);
			free(new_input);
		}
	}
	else
		add_var(*input);
	print_last_node();
}

char *lookup_var(char *var_name)
{
	t_var_list	*v;

	v = ms()->var_list;
	while (v)
	{
		if (ft_strcmp(v->key, var_name) == 0)
			return (ft_strdup(v->value));
		v = v->next;
	}
	return (ft_strdup(""));
}

char	*expand_variable(char *str)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	start = ft_strchr(str, '$');
	if (start == NULL || *(start + 1) == '\0' || *(start + 1) == '\0')
		return (ft_strdup(str));
	end = skip_variable(start);
	if (start + 1 == end)
		return (ft_strdup(str));
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	var_value = lookup_var(var_name); //empty string if doesnt exist, othervise the value
	free(var_name);
	temp = ft_strjoin(prefix, var_value);
	expanded_str = ft_strjoin(temp, expand_variable(end)); //recursively solve all the rest of the variables in the same WORD
	free(temp);
	free(prefix);
	return (expanded_str);
}
