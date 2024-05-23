/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 13:27:32 by lkilpela         ###   ########.fr       */
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
	char			*equal_pos;
	char			*value;
	char			*prefix;
	char 			*new_input;
	
	handle_empty_var_assignment(input);
	new_input = NULL;
	equal_pos = ft_strchr(*input, EQUAL_SIGN);
	if (equal_pos)
	{
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		value = check_quotes_and_expand(equal_pos + 1);
		new_input = ft_strjoin(prefix, value);
		if (new_input)
		{
			add_var(new_input);
			free(prefix);
			free(new_input);
		}
	}
	else
		add_var(*input);
	print_last_node();
}

char	*lookup_var(char *var_name)
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
