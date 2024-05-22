/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 18:13:16 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote_type	update_quote_type(t_quote_type quote_type, char c)
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

char	*expand_var(char *s, char **str)
{
	char	*end;
	char	*name;
	char	*value;
	char	*new_str;
	char	*final_str;

	end = skip_variable(s);
	name = ft_strndup(s + 1, end - s - 1);
	value = lookup_var(name);
	free(name);
	new_str = ft_strjoin(ft_strndup(*str, s - *str), value);
	final_str = ft_strjoin(new_str, ft_strdup(end));
	s = final_str + ft_strlen(new_str);
	free(value);
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
