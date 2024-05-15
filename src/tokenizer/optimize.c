/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 15:24:43 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char *next_token(char *str)
{
	while (*str)
	{
		if (is_whitespace(*str))
			str = skip_whitespaces(str);
		else if (is_word(*str))
			str = skip_word(str);
		else if (is_operator(*str))
			str = skip_op(str);
		else if (is_quote(*str))
			str = skip_quote(str);
		else if (*str == '$')
			str = skip_variable(str);
		else
			break;
	}
	return (str);
}

int get_token_len(char *str)
{
	char	*end;
	int		len;

	end = next_token(str);
	len = end - str;
	if (is_quote(*str))
		len -= 2;
	else if (*str == '$')
	{
		if(*(str + 1) == '?')
			len = 2;
		else
			len -= 1;
	}
	return (len);
}

t_token_type	get_token_type(char *str)
{
	if (*str == '\'')
		return (S_QUOTE);
	else if (*str == '\"')
		return (D_QUOTE);
	else if (ft_strcmp(str, "<<") == 0)
		return (OP_DLESS);
	else if (ft_strcmp(str, ">>") == 0)
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else if (str[0] == '$')
		return (VAR);
	else if (is_word(*str))
		return (WORD);
	else
		return (UNKNOWN);
}

t_token	create_token(char *str)
{
	t_token	a_token;
	char	*s;
	int		len;

	s = str;
	len = get_token_len(str);
	if (is_quote(*str) || *str == '$')
		s++;
	a_token.value = ft_strndup(s, len);
	a_token.type = get_token_type(str);
	return (a_token);
}

t_token_list	*tokenizer(char **str)
{
	
}