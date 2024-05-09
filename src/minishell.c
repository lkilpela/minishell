/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/07 21:35:48 by aklein           ###   ########.fr       */
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

t_list	*lexer(char *str)
{
	t_list	*tokens;
	t_list	*new;
	t_token	*current_tok;
	int		word_len;

	str = ft_skip_whitespace(str);
	tokens = NULL;
	while (*str)
	{
		str = ft_skip_whitespace(str);
		current_tok = ft_calloc(1, sizeof(t_token));
		if (ft_strchr(TOKENS, *str))
		{
			current_tok->type = *str;
			current_tok->str = NULL;
			new = ft_lstnew((void *)current_tok);
			ft_lstadd_back(&tokens, new);
			str++;
		}
		else
		{
			word_len = word_length(str);
			current_tok->type = WORD;
			current_tok->str = ft_substr(str, 0, word_len);
			new = ft_lstnew((void *)current_tok);
			ft_lstadd_back(&tokens, new);
			str += word_len;
		}
	}
	return (tokens);
}

int main(void)
{
	char *line;
	t_list *tokens;
	t_token *tok;

	while (42)
	{
		line = readline("Minishell:>");
		tokens = lexer(line);
		while (tokens)
		{
			tok = (t_token *)(tokens->content);
			printf("<type: '%c' str: <%s>\n", tok->type, tok->str);
			tokens = tokens->next;
		}
		// printf("%s\n", line);
		free(line);
	}
	return (0);
}