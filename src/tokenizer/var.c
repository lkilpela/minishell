/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 11:40:52 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

/*char *find_var_end(char *str)
{
	char	*end;

	end = str + 1; // skip dollar sign
	if (*end == '?')
		end++; // special case for '$?'
	else
		while (ft_isalnum(*end) || *end == '_')
			end++;
	return (end);
}*/

t_var	*expand_variables(t_token *token)
{
	t_var	*var;
	char	*env_value;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	if (token->type == VAR)
	{
		// store token.value to var.name
		var->name = ft_strdup(token->value);
		if (!var->name)
		{
			free(var);
			return (NULL);
		}
		env_value = getenv(token->value);
		if (env_value)
		{
			var->value = ft_strdup(env_value);
			if (!var->value)
			{
				free(var->name);
				free(var);
				return (NULL);
			}
		}
		else
			var->value = NULL;
	}
	return (var);
}

