/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 09:18:07 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote_type	identify_quotes(char **str)
{
	size_t			len;
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;
	len = ft_strlen(*str);
	if ((*str)[0] == S_QUOTE && (*str)[len - 1] == S_QUOTE)
	{
		(*str)[len - 1] = '\0';
		(*str)++;
		quote_type = SINGLE_QUOTE;
	}
	else if ((*str)[0] == D_QUOTE && (*str)[len - 1] == D_QUOTE)
	{
		(*str)[len - 1] = '\0';
		(*str)++;
		quote_type = DOUBLE_QUOTE;
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

	if ((quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE))
		expanded = expand_if_needed(str);
	else
		expanded = ft_strdup(str);
	return (expanded);
}
