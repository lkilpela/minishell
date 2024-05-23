/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:56:49 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 22:08:34 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_len(char *str)
{
	int	inquote;
	int	len;

	len = 0;
	inquote = 0;
	if (is_double_operator(str))
		return (2);
	if (is_operator(*str))
		return (1);
	while (*str)
	{
		if (inquote && is_quote(*str))
			inquote -= *str;
		else if (is_quote(*str))
			inquote += *str;
		else if (!inquote && !is_word(*str))
			return (len);
		else if (inquote && (*str == '|' || *str == '<' || *str == '>'))
            return (len);
		len++;
		str++;
	}
	printf("str: %s, len: %d\n", str, len);
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
	token->value = check_quotes_and_expand(value);
	token->type = type;
	return (token);
}
