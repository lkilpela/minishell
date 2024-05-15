/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 08:40:23 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char *find_var_end(char *str)
{
	char	*end;

	end = str + 1; // skip dollar sign
	if (*end == '?')
		end++; // special case for '$?'
	else
		while (ft_isalnum(*end) || *end == '_')
			end++;
	return (end);
}

void	expand_variables(char *str)
{
	char *var_value;
	const char *var_name = "USER";

	var_value = getenv(var_name);
	printf("var_value: %s\n", var_value);
}

