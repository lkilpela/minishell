/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:22:23 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 14:25:58 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_quote_type	identify_quotes(char **str)
{
	size_t			len;
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;
	len = ft_strlen(*str);
	if ((*str)[0] == '\'' && (*str)[len - 1] == '\'')
	{
		(*str)[len - 1] = '\0';
		(*str)++;
		quote_type = SINGLE_QUOTE;
	}
	else if ((*str)[0] == '\"' && (*str)[len - 1] == '\"')
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
	if (ft_strchr(str, '$'))
	{
		expanded = expand_variable(str, v);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (str);
}

char 	*handle_quotes(char *str, t_var_list *v)
{
	t_quote_type quote_type;
	char *expanded;

	quote_type = identify_quotes(&str);
	if (quote_type == DOUBLE_QUOTE)
		expanded = expand_if_needed(str, v);
	else
		expanded = ft_strdup(str);
	return (expanded);
}
