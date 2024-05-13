/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 22:17:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/tokenizer.h"

static int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_double_operator(char *str)
{
	return (*str == '>' && *(str + 1) == '>') 
		|| (*str == '<' && *(str + 1) == '<');
}

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str) && !is_operator(*str)
		&& !is_quote(*str))
		str++;
	return (str);
}

char *skip_op(char *str)
{
	if (is_operator(*str))
		str++;
	return (str);
}

char *skip_quote(char *str)
{
	int	in_quote = 1;

	str++;
	while (in_quote)
	{
		if (is_quote(*str))
			in_quote = 0;
		else
			str++;
	}
	if (!in_quote)
		str++;
	return (str);
}

int count_tokens(char *str)
{
	int count = 0;

	while (*str)
	{
		str = skip_whitespaces(str);
		if (*str && !is_operator(*str) && !is_quote(*str))
		{
			count++;
			str = skip_word(str);
		}
		else if (*str && is_operator(*str))
		{
			count++;
			str = skip_op(str);
		}
		else if (*str && is_quote(*str))
		{
			count++;
			str = skip_quote(str);
		}
	}
	return (count);
}

int	len_inquote(char *str)
{
	char *end;
	int len = 0;
	
	//printf("str before increment: %s\n", str);
	str++;
	//printf("str after increment: %s\n", str);
	end = str;
	end = skip_quote(str);
	end--;
	//printf("end string: %s\n", end);
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
		//printf("inquote: %s\n", str);
		len = len_inquote(str);
		//printf("len_inquote: %d\n", len);
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

t_token_list	*new_node(t_token token)
{
	t_token_list *lst;

	lst = malloc(sizeof(t_token_list));
	if (!lst)
		return (NULL);
	lst->token = token;
	lst->next = NULL;
	return (lst);	
}

t_token_list	*last_node(t_token_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
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

void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	free(lst->token.value);
	free(lst);
}

void	free_list(t_token_list **lst)
{
	t_token_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		delone_node(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void	print_tokens(t_token_list *lst)
{
    t_token_list	*temp;

	temp = lst;
    while (temp) 
	{
        printf("Value: %s, Type: %d\n", temp->token.value, temp->token.type);
        temp = temp->next;
    }
}


int main()
{
	char *str = "echo \" Hello\"  \'World!\' >> << |ls";
	t_token_list *lst = tokenize_input(str);
	print_tokens(lst);
	free_list(&lst);
}
