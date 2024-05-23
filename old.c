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