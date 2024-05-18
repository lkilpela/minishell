/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 02:55:39 by aklein           ###   ########.fr       */
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
	char	*expanded;

	if (token->type == WORD)
	{
		// "echo$ARG"eee"" or "echo$ARG" or"echo"eee""
		if (is_double_quoted(token->value))
		{
			unquoted = remove_outer_quotes(token->value);
			// unquoted = echo$ARG"eee" or echo$ARG or echo"eee"
			// ARG=" la hello world"
			if (ft_strchr(unquoted, '$') != NULL)
			{
				expanded = expand_variable(unquoted, v);
				free(token->value);
				// expanded = echo la hello worldd"eee" or echo la hello world
				token->value = expanded;
			}
			else // token->value = echo"eee"
			{
				free(token->value);
				token->value = unquoted;
			}
		}
		// 'echo$ARG"eee"' or 'echo$ARG' or 'echo"eee"'
		else if (is_single_quoted (token->value))
		{
			unquoted = remove_outer_quotes(token->value);
			free(token->value);
			token->value = unquoted;
			// unquoted: echo$ARG"eee" or echo$ARG or echo"eee"
		}
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
