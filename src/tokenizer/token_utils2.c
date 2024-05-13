/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 22:26:42 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:26:58 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

int	len_inquote(char *str)
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

char *find_token_end(char *str)
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

int get_token_len(char *str)
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