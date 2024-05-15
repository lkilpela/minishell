/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 10:39:09 by lkilpela         ###   ########.fr       */
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
		len -= 1;
	return (len);
}

t_token	create_token(char *str)
{
	t_token	a_token;
	int		len;

	a_token.value = NULL;
	a_token.type = -1;
	len = get_token_len(str);
	if (is_quote(str[0]))
		a_token.value = ft_strndup(str + 1, len);
	else if (str[0] == '$')
		a_token.value = ft_strndup(str, len);
	else
		a_token.value = ft_strndup(str, len);
	a_token.type = get_token_type(str);
	return (a_token);
}

t_token_list	*tokenize_input(char *str)
{
	t_token_list	*lst;
	t_token			token;
	int				var_expansion;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		token = create_token(str);
		if (is_quote(*str))
		{
			var_expansion = 0;
			str = handle_quotes(str, &var_expansion);
			if (var_expansion == 1)
			{
				//performing var expansion
			}
		}
		else if (*str == '$') // dollar sign
		{
			//create a token for variable name, replace it with variable's value
		}
		else if (!is_operator(*str))
			str = skip_word(str);
		else if (is_double_operator(str))
		{
			
				// create a token for << operator
				// read the next token as heredoc delimiter
				// if the delim is quoted
					//set a flg to disable variable expansion in heredoc
				// else
					//set a flag to enable variable expansion in heredoc
				str++;
		}	
		else
			str = skip_op(str);
		append_node(&lst, token);
	}
	return (lst);
}