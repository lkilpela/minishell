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

static char	*remove_outer_quotes(char *str)
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


/*static t_quote_type	identify_quotes(char **str)
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
}*/