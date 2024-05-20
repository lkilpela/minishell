/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 15:38:09 by lkilpela         ###   ########.fr       */
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
static char	*expand_if_needed(char *str, t_var_list *v)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(str, DOLLAR_SIGN))
	{
		expanded = expand_variable(str, v);
		printf("Expanded token: %s\n", expanded);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (str);
}

char 	*handle_quotes(char *str, t_var_list *v)
{
	t_quote_type	quote_type;
	char			*expanded;

	quote_type = identify_quotes(&str);
	if (quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE)
		expanded = expand_if_needed(str, v);
	else
		expanded = ft_strdup(str);
	return (expanded);
}
