/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:06:04 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/04 04:13:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	has_quotes(char *value)
{
	while (*value)
	{
		if (is_quote(*value))
			return (1);
		value++;
	}
	return (0);
}

static int	contains_space(char *var)
{
	char	quote;

	quote = 0;
	while (*var)
	{
		if (!quote && is_whitespace(*var))
			return (1);
		if (!quote && is_quote(*var))
			quote = *var;
		else if (quote && *var == quote)
			quote = 0;
		var++;
	}
	return (0);
}

int	is_ambiguous(char *val, t_token_list *tokens)
{
	if (contains_space(val))
	{
		print_error(ERR_MS, tokens->value, ERR_AMBIGUOUS, 0);
		ms()->exit = 1;
		return (1);
	}
	return (0);
}
