/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/17 13:25:41 by lkilpela         ###   ########.fr       */
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

static char	*get_variable(char *var)
{
	char	*key;
	char	*value;
	char	*end;

	end = skip_variable(var);
	key = ft_safe_strndup(var + 1, end - var - 1);
	value = lookup_var(key);
	ft_free((void **)&key);
	return (value);
}

static int	special_case_dollar(char *var)
{
	if (*var == '$')
	{
		var++;
		if (*var == 0 || *var == '\'' || *var == '\"')
			return (1);
		if (*var == '_' || *var == '?')
			return (0);
		if (!ft_isalnum(*var))
			return (2);
	}
	return (0);
}

char	*exp_next_var(char *var, char **start)
{
	char	*new;
	char	*beginning;
	char	*final;
	char	*value;
	int		ret_index;

	beginning = ft_safe_strndup(*start, var - *start);
	value = get_variable(var);
	new = ft_safe_strjoin(beginning, value);
	ret_index = ft_strlen(new) + special_case_dollar(var);
	ft_free((void **)&beginning);
	ft_free((void **)&value);
	final = ft_safe_strjoin(new, skip_variable(var));
	ft_free((void **)&new);
	*start = final;
	return (*start + ret_index);
}

char	*exp_word(char *str_start)
{
	t_quote_type	quote;
	char			*str;

	str = str_start;
	quote = NO_QUOTE;
	while (*str)
	{
		quote = update_quote_type(quote, *str);
		if (quote != SINGLE_QUOTE && *str == '$')
			str = exp_next_var(str, &str_start);
		else
			str++;
	}
	return (str_start);
}
