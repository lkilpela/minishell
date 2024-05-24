/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:56:49 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 23:46:26 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_len(char *str)
{
	char	inquote;
	int		len;

	len = 0;
	inquote = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			if (inquote == 0)
				inquote = *str;
			else if (inquote == *str)
				inquote = 0;
		}
		else if (!inquote)
		{
			if (is_operator(*str) || is_double_operator(str) || !is_word(*str))
			{
				if (len > 0)
					break ;
				if (is_double_operator(str))
					return (2);
				return (1);
			}
		}
		len++;
		str++;
	}
	return (len);
}

static t_token_type	get_token_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (OP_DLESS);
	else if (!ft_strncmp(str, ">>", 2))
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else if (*str == '$')
		return (VAR);
	else if (is_word(*str))
		return (WORD);
	else
		return (UNKNOWN);
}

static void	extract_token(char *str, char **value, t_token_type *type)
{
	int	len;

	len = token_len(str);
	*value = ft_strndup(str, len);
	*type = get_token_type(str);
}

t_token	*create_token(char *str)
{
	static int		last_was_dless = 0;
	t_token			*token;
	char			*value;
	t_token_type	type;

	extract_token(str, &value, &type);
	if (!value)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->value = expand_with_condition(value, last_was_dless);
	token->type = type;
	if (token->type == OP_DLESS)
		last_was_dless = 1;
	else
		last_was_dless = 0;
	return (token);
}
