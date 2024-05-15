/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 23:04:38 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

t_token	create_token(char *str)
{
	t_token	a_token;
	int		len;

	a_token.value = NULL;
	a_token.type = -1;
	len = get_token_len(str);
	if (is_quote(*str))
	{
		a_token.quotes = *str;
		a_token.value = ft_strndup(str + 1, len);
	}
	else if (*str == '$')
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

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		token = create_token(str);
		if (is_quote(*str))
		{
			//str = handle_quotes(str, &var_expansion);
			//if (var_expansion == 1)
			//{
				//performing var expansion
			//}
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

/*// check quote type and set *var_expansion
char	*handle_quotes(char *str, int *var_expansion)
{
	char	quote_type;
	char	*end;

	quote_type = *str;
	if (quote_type == '\"')
		*var_expansion = 1;
	else
		*var_expansion = 0;
	str = skip_quote(str);
	return (str);
}

void	handle_double_quote(char *str);
void	handle_variable(char *str)
{
	// non-existent variable
	// variable followed by non-whitespace character
	// variable inside double quotes
}
void	handle_heredoc(char *str)
{
	// variable expansion inside heredoc
	// variable expasion inside quoted heredoc
	// variable as a heredoc delim
	// non-existent variable inside heredoc
	// variable followed by non-whitespace character inside heredoc
}
*/
int main()
{
	char *str = "    echo \" Hello\"  \'World!\' >> << |ls";
	t_token_list *lst = tokenize_input(str);
	print_tokens(lst);
	free_list(&lst);
}
