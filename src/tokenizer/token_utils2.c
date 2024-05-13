/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:37:51 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

static int	len_inquote(char *str)
{
	char *end;
	int len = 0;
	
	str++;
	end = str;
	end = skip_quote(str);
	end--;
	len = end - str;
	return (len);
}

static char	*find_token_end(char *str)
{
	char	*end;

	end = str;
	if (is_operator(*str))
		end++;
	else
		while (*end && !is_whitespace(*end) && !is_operator(*end))
			end++;
	return (end);
}

int	get_token_len(char *str)
{
	int		len;
	char	*end;
	
	if (is_quote(*str))
	{
		len = len_inquote(str);
		str++;
	}
	else if (is_double_operator(str))
	{
		len = 2;
	}
	else
	{
		end = find_token_end(str);
		len = end - str;
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
	else
		return (WORD);
}