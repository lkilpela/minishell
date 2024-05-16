/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/16 14:18:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char *remove_quotes(char *str)
{
	char *p = str;
	char *q = str;
	while (*p)
	{
		if (*p != '\"')
			*q++ = *p;
		p++;
	}
	*q = '\0';
	return (str);
}

static char *lookup_var(char *var_name, t_var_list *v)
{
	while (v)
	{
		if (ft_strcmp(v->current_var->name, var_name) == 0)
			return (ft_strdup(v->current_var->value));
		v = v->next;
	}
	return (NULL);
}

char *expand_variable(char *str, t_var_list *v)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	printf("input: %s\n", str);
	start = ft_strchr(str, '$');
	end = skip_variable(start);
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	printf("var_name: %s\n", var_name);
	var_value = lookup_var(var_name, v);
	printf("var_value: %s\n",var_value);
	if (var_value)
	{
		temp = ft_strjoin(prefix, var_value);
		expanded_str = ft_strjoin(temp, end);
		free(temp);
	}
	else	
		expanded_str = ft_strdup(str);
	free(prefix);
	return (expanded_str);
}

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

int 	token_len(char *str)
{
	char	*end;
	int		len;

	end = next_token(str);
	len = end - str;
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
	else if (is_word(*str))
		return (WORD);
	else
		return (UNKNOWN);
}

void	extract_token(char *str, char **value, t_token_type *type)
{
	int	len;
	
	len = token_len(str);
	*value = ft_strndup(str, len);
	*type = get_token_type(str);
}

t_token	*create_token(char *str)
{
	t_token 		*token;
	char			*value;
	t_token_type	type;

	value = NULL;
	type = -1;
	extract_token(str, &value, &type);
	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		free(value);
	token->value = value;
	token->type = type;
	return (token);
}

t_token_list *create_token_node(char *str)
{
	t_token_list *node;

	node = malloc(sizeof(t_token_list));
	if (!node)
		return (NULL);
	node->token = create_token(str);
	if (!node->token)
	{
		free(node);
		return (NULL);		
	}
	node->next = NULL;
	return (node);
}

void	add_token_to_list(t_token_list **lst, t_token *node)
{
	t_token_list	*last;

	if (*lst == NULL)
		*lst = node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

void	add_token(t_token_list **lst, char *str)
{
	t_token_list	*node;
	t_token_list	*t;
	char			*value;
	t_token_type	type;

	value = NULL;
	type = -1;
	extract_token(str, &value, &type);
	if (!value)
		return ;
	t = *lst;
	node = create_token(str);
	if (!node)
		return ;
	add_token_to_list(lst, node);
}

t_token_list tonkenizer(char *str)
{
	t_token_list	*lst;
	char			*next;

	lst = NULL;
	while (*str)
	{
		add_token(&lst, str);
		next = next_token(str);
		str = next;
	}
	return (lst);
}


/*t_token	create_token(char *str)
{
	t_token	a_token;
	char	*s;
	int		len;

	s = str;
	len = get_token_len(str);
	if (is_quote(*str) || *str == '$')
		s++;
	a_token.value = ft_strndup(s, len);
	a_token.type = get_token_type(str);
	return (a_token);
}*/

/*int get_token_len(char *str, t_var_list *v)
{
	char	*end;
	int		len;

	
	len = end - str;
	if (is_quote(*str))
		len -= 2;
	else if (*str == '$')
	{
		if(*(str + 1) == '?')
			len = 2;
		else
			len -= 1;
	}
	return (len);
}*/