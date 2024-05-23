char	*remove_outer_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return str;
	if (is_quote(str[0])&& is_quote(str[len - 1]))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
	return (str);
}

void	process_var_assigment(char **input, t_var_list *v)
{
	char	*equal_pos;
	char	*expanded;
	char	*prefix;
	char 	*new_input;
	char	*unquoted;
	
	if (*input == NULL || **input == '\0')
	{
		add_var(&v, *input);
		return ;
	}
	new_input = NULL;
	equal_pos = ft_strchr(*input, '=');
	if (equal_pos)
	{
		unquoted = remove_outer_quotes(equal_pos + 1);
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		expanded = expand_if_needed(unquoted, v);
		if (expanded)
		{
			new_input = ft_strjoin(prefix, expanded);
			free(prefix);
			if (new_input)
			{
				add_var(&v, new_input);
				free(new_input);
			}
		}
		else
		{
			free(*input); // If the token is not quoted at all, free the original value
			*input = unquoted;
		}
		add_var(&v, new_input);// name: ARG value: lumik
	}
	else
		add_var(&v, *input);
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

static void	process_token(t_token *token)
{
	char	*value;

	value = handle_quotes(token->value);
	if (value)
	{
		//free(token->value);
		token->value = value;
	}
	else
		token->value = ft_strdup("");
	
}

// switches between NO_QUOTE, SINGLE_QUOTE, and DOUBLE_QUOTE 
// every time it encounters a quote character
static t_quote_type	identify_quotes(char *str)
{
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;

	while (*str)
	{
		if (*str == S_QUOTE)
		{
			if (quote_type == SINGLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = SINGLE_QUOTE;
		}
		else if (*str == D_QUOTE)
		{
			if (quote_type == DOUBLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = DOUBLE_QUOTE;
		}
		str++;
	}
	return (quote_type);
}

// toggle quotes and determine the content inside quotes
static t_quote_type	identify_quotes(char **str)
{
	size_t			len;
	t_quote_type	quote_type;

	quote_type = NO_QUOTE;
	len = ft_strlen(*str);
	if ((*str)[0] == S_QUOTE && (*str)[len - 1] == S_QUOTE)
	{
		(*str)[len - 1] = '\0';
		(*str)++;
		quote_type = SINGLE_QUOTE;
	}
	else if ((*str)[0] == D_QUOTE && (*str)[len - 1] == D_QUOTE)
	{
		(*str)[len - 1] = '\0';
		(*str)++;
		quote_type = DOUBLE_QUOTE;
	}
	return (quote_type);
}

char	*remove_outer_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len < 2)
		return str;
	if (is_quote(str[0])&& is_quote(str[len - 1]))
	{
		ft_memmove(str, str + 1, len - 2);
		str[len - 2] = '\0';
	}
	return (str);
}

char	*expand_variable(char *str, t_quote_type quote_type)
{
	char	*start;
	char	*prefix;
	char	*end;
	char	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	start = str;
	while (*start)
	{
		if (*start == S_QUOTE && (quote_type == NO_QUOTE || quote_type == SINGLE_QUOTE))
		{
			if (quote_type == SINGLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = SINGLE_QUOTE;
		}
		else if (*start == D_QUOTE && (quote_type == NO_QUOTE || quote_type == DOUBLE_QUOTE))
		{
			if (quote_type == DOUBLE_QUOTE)
				quote_type = NO_QUOTE;
			else
				quote_type = DOUBLE_QUOTE;
		}
		if (*start == '$' && (quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE))
		{
			end = skip_variable(start);
			if (start + 1 == end)
				return (ft_strdup(str));
			prefix = ft_strndup(str, start - str);
			var_name = ft_strndup(start + 1, end - start - 1);
			var_value = lookup_var(var_name); //empty string if doesnt exist, othervise the value
			free(var_name);
			temp = ft_strjoin(prefix, var_value);
			if (end)
				expanded_str = ft_strjoin(temp, expand_variable(end, NO_QUOTE)); //recursively solve all the rest of the variables in the same WORD
			else
				expanded_str = ft_strdup(temp);
			free(temp);
			free(prefix);
			return (expanded_str);
		}
		start++;
	}
	return (ft_strdup(str));
}


static char	*expand_if_needed(char *str)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(str, DOLLAR_SIGN))
	{
		expanded = expand_variable(str);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (str);
}

char 	*handle_quotes(char *str)
{
	char			*expanded;
	t_quote_type 	quote_type;

	quote_type = identify_quotes(str);
	printf("quote_type: 1(s) 2(d): %d\n", quote_type);
	if ((quote_type == DOUBLE_QUOTE || quote_type == NO_QUOTE))
		expanded = expand_if_needed(str);
	else
		expanded = ft_strdup(str);
	return (expanded);
}

/*char	*expand_variable(char *str)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	start = ft_strchr(str, '$');
	if (start == NULL || *(start + 1) == '\0' || *(start + 1) == '\0')
		return (ft_strdup(str));
	end = skip_variable(start);
	if (start + 1 == end)
		return (ft_strdup(str));
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	var_value = lookup_var(var_name); //empty string if doesnt exist, othervise the value
	free(var_name);
	temp = ft_strjoin(prefix, var_value);
	expanded_str = ft_strjoin(temp, expand_variable(end)); //recursively solve all the rest of the variables in the same WORD
	free(temp);
	free(prefix);
	return (expanded_str);
}*/

/*char	*check_quotes_and_expand(char *str)
{
	t_quote_type	quote_type;
	char			*s;

	quote_type = NO_QUOTE;
	s = str;
	// '$some'"echo "$HOME"" -> final_str: '$some'"echo "User/lumik" $USER"
	while (*s)
	{
		if (quote_type == NO_QUOTE)
		{
			if (*s == S_QUOTE)
				quote_type = SINGLE_QUOTE;
			else if (*s == D_QUOTE)
				quote_type = DOUBLE_QUOTE;
		}
		else if (quote_type == SINGLE_QUOTE)
		{
			if (*s == S_QUOTE)
				quote_type = NO_QUOTE;
		}
		else if (quote_type == DOUBLE_QUOTE)
		{
			if (*s == D_QUOTE)
				quote_type = NO_QUOTE;
		}
		if (quote_type != SINGLE_QUOTE && *s == '$')
		{
			char *end = skip_variable(s);
			char *name = ft_strndup(s + 1, end - s - 1);
			char *value = lookup_var(name);
			free(name);

			char *prefix = ft_strndup(str, s - str);
			char *posfix = ft_strdup(end);
			char *new_str = ft_strjoin(prefix, value);
			char *final_str = ft_strjoin(new_str, posfix);

			s = final_str + ft_strlen(new_str);
			
			free(value);
			free(prefix);
			free(posfix);
			free(new_str);
			str = final_str;		
		}	
		s++;
	}
	return (str);
}*/





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

static void	process_token(t_token *token)
{
	char	*value;

	value = NULL;
	value = check_quotes_and_expand(token->value);
	if (value)
	{
		//free(token->value);
		token->value = value;
	}
	else
		token->value = ft_strdup("");
	
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
	process_token(node->token);
	node->next = NULL;
	return (node);
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
	if (!node)
		return ;
	add_token_to_list(lst, node);
}


int	token_len(char *str)
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