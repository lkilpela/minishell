/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 09:21:46 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote_type	identify_quotes(char *str)
{
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;

	while (*str)
	{
		if (*str == S_QUOTE)
		{
			if (quote_type == SINGLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = SINGLE_QUOTE;
		}
		else if (*str == D_QUOTE)
		{
			if (quote_type == DOUBLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = DOUBLE_QUOTE;
		}
		str++;
	}
	return (quote_type);
}

static char	*expand_if_needed(char *str)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(str, DOLLAR_SIGN))
	{
		expanded = expand_variable(str);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (str);
}

char 	*handle_quotes(char *str)
{
	char			*expanded;
	t_quote_type 	quote_type;

	quote_type = identify_quotes(&str);
	if ((quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE))
		expanded = expand_if_needed(str);
	else
		expanded = ft_strdup(str);
	return (expanded);
}
