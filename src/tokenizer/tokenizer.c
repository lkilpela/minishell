/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 23:45:57 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

/*static void	process_token(t_token *token, t_var_list *v)
{
	char	*value;

	value = handle_quotes(token->value, v);
	if (value)
	{
		free(token->value);
		token->value = value;
	}
}*/

static t_token_list *create_token_node(char *str)
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
	//process_token(node->token, v);
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
static void	add_token(t_token_list **lst, char *str)
{
	t_token_list	*node;
	char			*value;
	t_token_type	type;

	value = NULL;
	type = -1;
	extract_token(str, &value, &type);
	if (!value)
		return ;
	node = create_token_node(str);
	print_a_token(node);
	if (!node)
		return ;
	add_token_to_list(lst, node);
}

static void	process_token(t_token_list **t, t_var_list *v)
{
	char	*new_value;

	new_value = handle_quotes((*t)->token->value, v);
	printf("new_value: %s\n", new_value);
	if (new_value)
	{
		free((*t)->token->value);
		(*t)->token->value = new_value;
	}
}

// converts a string into a list of tokens
t_token_list	*tokenizer(char *str, t_var_list *v)
{
	t_token_list	*t;

	t = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		add_token(&t, str);
		process_token(&t, v);
		if (ft_strchr(t->token->value, ' '))
		{
			add_token(&t, t->token->value);
			t->token->value += token_len(t->token->value);
			printf("re_tokenize: %s\n", t->token->value);
			t = t->next;
		}
		str += token_len(str);
		//printf("value_str: %s and len: %d\n", str, token_len(str));
	}
	return (t);
}
