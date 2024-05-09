/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/09 15:41:45 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	word_length(char *str)
{
	int	i;

	i = 0;
	while (*str && !ft_strchr(TOKENS, *str) && !ft_is_whitespace(*str))
	{
		i++;
		str++;
	}
	return (i);
}

char	*ft_skip_whitespace(char *str)
{
	while (ft_is_whitespace(*str))
		str++;
	return (str);
}

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
}

int main(void)
{
	char *line;
	t_tok_list *tok;

	while (42)
	{
		line = readline("Minishell:<");
		tok = lexer(line);
		while (tok)
		{
			printf("<type: '%c' str: '%s'\n", tok->type, tok->str);
			tok = tok->next;
		}
		// printf("%s\n", line);
		free(line);
	}
	return (0);
}