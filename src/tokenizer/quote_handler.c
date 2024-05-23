/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 11:50:25 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*check_quotes_and_expand(char *str)
{
	t_quote_type	quote_type;
	char			*s;

	quote_type = NO_QUOTE;
	s = str;
	// '$some'"echo "$HOME"" -> final_str: '$some'"echo "User/lumik" $USER"
	while (*s)
	{
		if (quote_type == NO_QUOTE)
		{
			if (*s == S_QUOTE)
				quote_type = SINGLE_QUOTE;
			else if (*s == D_QUOTE)
				quote_type = DOUBLE_QUOTE;
		}
		else if (quote_type == SINGLE_QUOTE)
		{
			if (*s == S_QUOTE)
				quote_type = NO_QUOTE;
		}
		else if (quote_type == DOUBLE_QUOTE)
		{
			if (*s == D_QUOTE)
				quote_type = NO_QUOTE;
		}
		if (quote_type != SINGLE_QUOTE && *s == '$')
		{
			char *end = skip_variable(s);
			char *name = ft_strndup(s + 1, end - s - 1);
			char *value = lookup_var(name);
			free(name);

			char *prefix = ft_strndup(str, s - str);
			char *posfix = ft_strdup(end);
			char *new_str = ft_strjoin(prefix, value);
			char *final_str = ft_strjoin(new_str, posfix);

			s = final_str + ft_strlen(new_str);
			
			free(value);
			free(prefix);
			free(posfix);
			free(new_str);
			str = final_str;		
		}	
		s++;
	}
	return (str);
}
