/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/28 19:26:20 by aklein           ###   ########.fr       */
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

char	*lookup_var(char *var_name)
{
	t_var_list	*v;

	v = ms()->var_list;
	if (*var_name == '?')
		return (ft_safe_itoa(ms()->exit));
	while (v)
	{
		if (ft_strcmp(v->key, var_name) == 0)
			return (ft_safe_strdup(v->value));
		v = v->next;
	}
	return (ft_safe_strdup(""));
}

char	*expand_var(char *s, char **str)
{
	char	*end;
	char	*name;
	char	*value;
	char	*new_str;
	char	*final_str;

	end = skip_variable(s);
	name = ft_safe_strndup(s + 1, end - s - 1);
	value = lookup_var(name);
	ft_free((void **)&name);
	new_str = ft_safe_strjoin(ft_safe_strndup(*str, s - *str), value);
	final_str = ft_safe_strjoin(new_str, ft_safe_strdup(end));
	s = final_str + ft_strlen(new_str);
	ft_free((void **)&value);
	ft_free((void **)&new_str);
	*str = final_str;
	return (s);
}

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

char	*expand_with_condition(char *str, int last_was_dless)
{
	t_quote_type	quote_type;
	char			*s;

	quote_type = NO_QUOTE;
	s = str;
	while (*s)
	{
		quote_type = update_quote_type(quote_type, *s);
		if (quote_type != SINGLE_QUOTE && *s == '$')
		{
			if (last_was_dless == 1)
				return (ft_safe_strdup(s));
			else
				s = expand_var(s, &str);
		}
		else
			s++;
	}
	return (str);
}
