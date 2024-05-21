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

/*t_token	**split_token(t_token *token)
{
	t_token **words;
	int i;

	i = 0;
	if (ft_strchr(token->value, ' '))
		words = ft_split(token->value, ' ');
	while (words[i])
	{
		create_token(words[i]);
		i++;
	}
	return (words);
}*/

static void	process_word_token(t_token *token, t_var_list *v)
{
	char	*value;

	value = handle_quotes(token->value, v);
	if (value)
	{
		//free(token->value);
		token->value = value;
		//if (ft_strchr(token->value, ' '))
			//split_token(token->value);
	}
	else
		token->value = ft_strdup("");
	
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
		add_token(&lst, str, v);
		str += token_len(str);
	}
	//print_tokens(lst);
	return (lst);
}


t_token_list *retokenizer(t_token_list **t, t_var_list *v)
{
	t_token_list *tmp;
	t_token_list *prev;
	t_token_list *new_token;
	t_token_list *last_new_token;

	prev = NULL;
	if (t && *t)
	{
		tmp = *t;
		while (tmp)
		{
			if (ft_strchr(tmp->token->value, ' '))
			{
				new_token = tokenizer(tmp->token->value, v);
				last_new_token = new_token; // last_new_token points to the first node
				while (last_new_token->next)//as long as the next node exits
					last_new_token = last_new_token->next; //move to next node
				if (tmp == *t)
					*t = new_token;
				else
					prev->next = new_token;
				last_new_token->next = tmp->next;

				free(tmp->token->value);
				free(tmp);
				tmp = new_token;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
	print_tokens(*t);
	return (*t);
}