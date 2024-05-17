/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/17 20:43:07 by lkilpela         ###   ########.fr       */
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

int	has_special_char(char *str)
{
	while (*str)
	{
		if (*str == '$' || is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

static t_token_type	get_token_type(char *str)
{
	// if (*str == '\'')
	// 	return (S_QUOTE);
	// else if (*str == '\"')
	// 	return (D_QUOTE);
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
	else if (str[0] == '$')
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
		free(value);
	token->value = value;
	token->type = type;
	return (token);
}

void	process_token(t_token *token, t_var_list *v)
{
	char	*unquoted;
	char	*expanded;

	// "echo$ARG"eee"" or "echo"eee"" or 'echo"eee"'
	if (token->type == D_QUOTE || token->type == S_QUOTE)
	{
		unquoted = remove_quotes(token->value);
		// unquoted = echo$ARGeee or echoeee
		// ARG=" la hello world"
		if (token->type == D_QUOTE && ft_strchr(unquoted, '$') != NULL)
		{
			expanded = expand_variable(unquoted, v);
			free(token->value);
			// expanded = echo la hello wolrdeeee
			token->value = expanded;
		}
		else // token->value = echoeee(D_QUOTE) or echo"eee" (S_QUOTE)
		{
			free(token->value);
			token->value = unquoted;
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
	process_token(node->token, v);
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
		"S_QUOTE",
		"D_QUOTE",
		"VAR",
		"T_NEWLINE",
		"T_SPACE",
		"COMPLEX_WORD",
		"UNKNOWN"
	};

	return (type_str[e]);
}

static void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	free(lst->token->value);
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

void print_tokens(t_token_list *lst)
{
	while (lst)
	{
		printf("Value: %s \t\t Type: %s\n", lst->token->value, get_type_str(lst->token->type));
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