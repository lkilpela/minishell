/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 12:13:52 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

static int	token_len(char *str)
{
	int	inquote;
	int	len;

	len = 0;
	inquote = 0;
	if (is_double_operator(str))
		return (2);
	if (is_operator(*str))
		return (1);
	while (*str)
	{
		if (inquote && is_quote(*str))
			inquote -= *str;
		else if (is_quote(*str))
			inquote += *str;
		else if (!inquote && !is_word(*str))
			return (len);
		len++;
		str++;
	}
	return (len);
}

static t_token_type	get_token_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (OP_DLESS);
	else if (!ft_strncmp(str, ">>", 2))
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else if (*str == '$')
		return (VAR);
	else if (is_word(*str))
			return (WORD);
	else
		return (UNKNOWN);
}

static void	extract_token(char *str, char **value, t_token_type *type)
{
	int	len;
	
	len = token_len(str);
	*value = ft_strndup(str, len);
	*type = get_token_type(str);
}

static t_token	*create_token(char *str)
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
	{
		free(value);
		return (NULL);
	}
	token->value = value;
	token->type = type;
	return (token);
}

int	is_double_quoted(char *str)
{
	char	*end;

	if (*str != '"')
		return (0);
	end = skip_quote(str);
	if (!end || end != str + ft_strlen(str))
		return (0);
	return (1);
}

int	is_single_quoted(char *str)
{
	char	*end;

	if (*str != '\'')
		return (0);
	end = skip_quote(str);
	if (!end || end != str + ft_strlen(str))
		return (0);
	return (1);
}

static void	process_word_token(t_token *token, t_var_list *v)
{
	char	*unquoted;
	char	*expanded;

	if (token->type == WORD || token->type == VAR)
	{
		// "echo$ARG"eee"" or "echo$ARG" or"echo"eee""
		// unquoted = echo$ARG"eee" or echo$ARG or echo"eee"
		// ARG=" la hello world"
		unquoted = remove_outer_quotes(token->value);
		if (ft_strchr(unquoted, '$') != NULL)
		{
			expanded = expand_variable(unquoted, v);
			free(token->value);
			// expanded = echo la hello worldd"eee" or echo la hello world
			token->value = expanded;
		}
		else // not double quoted or it doesn't contain a $
			token->value = unquoted;
	}
}

static t_token_list *create_token_node(char *str, t_var_list *v)
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
	process_word_token(node->token, v);
	node->next = NULL;
	return (node);
}

// add a node to a list
static void	add_token_to_list(t_token_list **lst, t_token_list *node)
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

// create new token and add to a list
static void	add_token(t_token_list **lst, char *str, t_var_list *v)
{
	t_token_list	*node;
	char			*value;
	t_token_type	type;

	value = NULL;
	type = -1;
	extract_token(str, &value, &type);
	if (!value)
		return ;
	node = create_token_node(str, v);
	if (!node)
		return ;
	add_token_to_list(lst, node);
}

// converts a string into a list of tokens
t_token_list	*tokenizer(char *str, t_var_list *v)
{
	t_token_list	*lst;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		if (ft_strchr(str, '='))
			process_var_assigment(&str, v);
		add_token(&lst, str, v);
		str += token_len(str);
	}
	return (lst);
}

static char	*get_type_str(int e)
{
	static char	*type_str[] = {
		"WORD",
		"OP_PIPE",
		"OP_LESS",
		"OP_GREAT",
		"OP_DLESS",
		"OP_DGREAT",
		"VAR",
		"UNKNOWN"
	};

	return (type_str[e]);
}

void print_tokens(t_token_list *lst)
{
	while (lst)
	{
		printf(BLUE "token_value: %-20s token_type: %s\n" RESET, lst->token->value, get_type_str(lst->token->type));
		lst = lst->next;
	}
}

// static char *next_token(char *str)
// {
// 	if (is_whitespace(*str))
// 		str = skip_whitespaces(str);
// 	else if (is_word(*str))
// 		str = skip_word(str);
// 	else if (is_operator(*str))
// 		str = skip_op(str);
// 	else if (is_quote(*str))
// 		str = skip_quote(str);
// 	//else if (*str == '$')
// 		//str = skip_variable(str);
// 	return (str);
// }

// static int 	token_len(char *str)
// {
// 	char	*end;
// 	int		len;

// 	end = next_token(str);
// 	len = end - str;
// 	return (len);
// }
