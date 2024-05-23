/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 12:12:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_quote_type	update_quote_type(t_quote_type quote_type, char c)
{
	if (quote_type == NO_QUOTE)
	{
		if (c == S_QUOTE)
			return (SINGLE_QUOTE);
		else if (c == D_QUOTE)
			return (DOUBLE_QUOTE);
	}
	else if (quote_type == SINGLE_QUOTE && c == S_QUOTE)
		return (NO_QUOTE);
	else if (quote_type == DOUBLE_QUOTE && c == D_QUOTE)
		return (NO_QUOTE);
	return (quote_type);
}

char	*expand_var(char *s, char **str)
{
	char	*end;
	char	*name;
	char	*value;
	char	*prefix;
	char	*posfix;
	char	*new_str;
	char	*final_str;

	end = skip_variable(s);
	name = ft_strndup(s + 1, end - s - 1);
	value = lookup_var(name);
	free(name);
	prefix = ft_strndup(*str, s - *str);
	posfix = ft_strdup(end);
	new_str = ft_strjoin(prefix, value);
	final_str = ft_strjoin(new_str, posfix);
	s = final_str + ft_strlen(new_str);
	free(value);
	free(prefix);
	free(posfix);
	free(new_str);
	*str = final_str;
	return (s);
}

	// '$some'"echo "$HOME"" -> final_str: '$some'"echo "User/lumik" $USER"
char	*check_quotes_and_expand(char *str)
{
	t_quote_type	quote_type;
	char			*s;

	quote_type = NO_QUOTE;
	s = str;
	while (*s)
	{
		quote_type = update_quote_type(quote_type, *s);
		if (quote_type != SINGLE_QUOTE && *s == '$')
			s = expand_var(s, &str);
		else
			s++;
	}
	return (str);
}
