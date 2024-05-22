/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/22 23:38:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_quote_type	identify_quotes(char *str)
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

char 	*handle_quotes(char *str, t_quote_type quote_type)
{
	//t_quote_type	quote_type;
	char			*expanded;

	//quote_type = identify_quotes(str);
	if ((quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE)
		&& ft_strchr(str, DOLLAR_SIGN))
		expanded = expand_variable(str, quote_type);
	else
		expanded = ft_strdup(str);
	return (expanded);
}

char	*remove_outer_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return str;
	if (is_quote(str[0])&& is_quote(str[len - 1]))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
	return (str);
}