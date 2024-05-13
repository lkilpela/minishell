/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 19:48:28 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/tokenizer.h"
#include "split.c"

void init_token_list(t_token_list *lst)
{
	if (lst)
	{
		init_token(&lst->token);
		lst->next = NULL;
	}
}

void init_token(t_token *token)
{
	token->value = NULL;
	token->type = -1;
}

char *ft_strndup(char *str, size_t len)
{
	size_t		i;
	char	*dup;

	i = 0;
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int    ft_strcmp(char *s1, char *s2)
{
    while (*s1 || *s2)
    {
        if (*s1 != *s2)
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
    }
    return (0);
}

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

t_token	create_token(char *str)
{
	t_token	a_token;
	int		len;

	init_token(&a_token);
	len = get_token_len(str);
	a_token.type = get_token_type(str);
	a_token.value = ft_strndup(str, len);
	return (a_token);
}

t_token_list	*new_node(t_token token)
{
	t_token_list *lst;

	lst = malloc(sizeof(t_token_list));
	if (!lst)
		return (NULL);
	init_token_list(lst);
	lst->token = token;
	return (lst);	
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
		if (is_quote(*str))
		{
			token = create_token(str);
			append_node(&lst, token);
			str = skip_quote(str);
		} 
		else
		{
			if (!is_operator(*str))
			{
				append_node(&lst, token);
				str = skip_word(str);
			}
			else
			{
				append_node(&lst, token);
				if (is_double_operator(str))
					str++;
				str = skip_op(str);
			}
		}
	}
	return (lst);
}

int main()
{
	char **str = split_input("   echo \" Hello\"  \'World!\' >> << |ls");
	for(int i = 0; str[i]; i++)
	{
		t_token a_token = create_token(str[i]);
		printf("a_token.value: %s\n", a_token.value);
		printf("a_toke.type: %d\n", a_token.type);
	}

}
