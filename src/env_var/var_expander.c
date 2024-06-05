/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:41:46 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 23:18:21 by lkilpela         ###   ########.fr       */
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

static char	*exp_next_var(char *var, char **start)
{
	char	*new;
	char	*beginning;
	char	*final;
	char	*value;
	int		ret_index;

	beginning = ft_safe_strndup(*start, var - *start);
	value = get_variable(var);
	new = ft_safe_strjoin(beginning, value);
	ret_index = ft_strlen(new);
	ft_free((void **)&beginning);
	ft_free((void **)&value);
	final = ft_safe_strjoin(new, skip_variable(var));
	ft_free((void **)&new);
	*start = final;
	return (*start + ret_index);
}

char	*heredoc_exp(char *str_start)
{
	char	*str;

	str = str_start;
	while (*str)
	{
		if (*str == '$')
			str = exp_next_var(str, &str_start);
		else
			str++;
	}
	return (str_start);
}

char	*exp_word(char *str_start)
{
	t_quote_type	quote;
	char			*str;

	str = str_start;
	quote = NO_QUOTE;
	if ((str[0] == '$' && str[1] == '\0') ||
		(str[0] == '\'' && str[1] == '$' && str[2] == '\'' && str[3] == '\0') ||
		(str[0] == '"' && str[1] == '$' && str[2] == '"' && str[3] == '\0'))
	{
		return (ft_strdup(str));
	}
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
