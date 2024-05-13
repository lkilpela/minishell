/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:29:04 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

t_token_type get_token_type(char *str)
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

t_token	create_token(char *str)
{
	t_token	a_token;
	int		len;
	int		start;

	a_token.value = NULL;
	a_token.type = -1;
	len = get_token_len(str);
	
	if (is_quote(str[0]))
		a_token.value = ft_strndup(str + 1, len);
	else
		a_token.value = ft_strndup(str, len);
	a_token.type = get_token_type(str);
	return (a_token);
}

void	append_node(t_token_list **lst, t_token token)
{
	t_token_list	*last;

	if (!*lst)
		*lst = new_node(token);
	else
	{
		last = last_node(*lst);
		last->next = new_node(token);
	}	
}

t_token_list *tokenize_input(char *str)
{
	t_token_list	*lst;
	t_token			token;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break;
		token = create_token(str);
		if (is_quote(*str))
			str = skip_quote(str);
		else if (!is_operator(*str))
			str = skip_word(str);
		else
		{
			if (is_double_operator(str))
				str++;
			str = skip_op(str);
		}
		append_node(&lst, token);
	}
	return (lst);
}

int main()
{
	char *str = "    echo \" Hello\"  \'World!\' >> << |ls";
	t_token_list *lst = tokenize_input(str);
	print_tokens(lst);
	free_list(&lst);
}
