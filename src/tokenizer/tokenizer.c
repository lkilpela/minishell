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
	token->value = check_quotes_and_expand(value);
	token->type = type;
	return (token);
}

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

static void	add_token(t_token_list **lst, char *str)
{
	t_token_list	*node;

	node = create_token_node(str);
	if (!node)
		return ;
	add_token_to_list(lst, node);
}

// converts a string into a list of tokens
t_token_list	*tokenizer(char *str)
{
	t_token_list	*lst;

	lst = NULL;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break ;
		add_token(&lst, str);
		str += token_len(str);
	}
	return (lst);
}

t_token_list	*reprocess_token(t_token_list **t, t_token_list *tmp,
								t_token_list **prev)
{
	t_token_list	*new_token;
	t_token_list	*last_new_token;
	t_token_list	*next;

	new_token = tokenizer(tmp->token->value);
	if (!new_token)
		return (tmp->next);
	printf("new_token list: \n");
	print_tokens(new_token);
	last_new_token = new_token;
	while (last_new_token->next)
		last_new_token = last_new_token->next;
	if ((*prev))
		(*prev)->next = new_token;
	else
		*t = new_token;
	last_new_token->next = tmp->next;
	next = tmp->next;
	free(tmp);
	return (next);
}

// ls$ARG hello | echo < output
t_token_list	*retokenizer(t_token_list **t)
{
	t_token_list	*prev;
	t_token_list	*tmp;

	prev = NULL;	
	tmp = *t;
	while (tmp)
	{
		if (ft_strchr(tmp->token->value, ' '))
		{
			printf("Original list: \n");
			print_tokens(*t);
			tmp = reprocess_token(t, tmp, &prev);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}

	printf("Updated list: \n");
	print_tokens(*t);
	return (*t);
}
