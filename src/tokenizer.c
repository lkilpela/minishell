/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/09 22:28:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*

t_tok_list	*lexer(char *str)
{
	t_tok_list	*tokens;
	int			word_len;

	int		state = 0;
	str = ft_skip_whitespace(str);
	tokens = NULL;
	while (*str)
	{
		str = ft_skip_whitespace(str);
		if (!state && ft_strchr(TOKENS, *str))
		{
			if (*str == '\"')
			{
				state = 1;
				str++;
				continue ;
			}
			tok_lstadd_back(&tokens, NULL, *str);
			str++;
		}
		else
		{
			if (*str == '\"')
			{
				state = 0;
				str++;
				continue ;
			}
			word_len = word_length(str);
			tok_lstadd_back(&tokens, ft_substr(str, 0, word_len), WORD);
			str += word_len;
		}
	}
	return (tokens);
}*/