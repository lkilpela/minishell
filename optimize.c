#include <minishell.h>

typedef enum e_quote_type
{
    NO_QUOTE,
    SINGLE_QUOTE,
    DOUBLE_QUOTE
}			t_quote_type;

t_quote_type	remove_outer_quotes(char **str)
{
    size_t	len;
    t_quote_type quote_type = NO_QUOTE;

    len = ft_strlen(*str);
    if ((*str)[0] == '\'' && (*str)[len - 1] == '\'')
    {
        (*str)[len - 1] = '\0';
        (*str)++;
        quote_type = SINGLE_QUOTE;
    }
    else if ((*str)[0] == '\"' && (*str)[len - 1] == '\"')
    {
        (*str)[len - 1] = '\0';
        (*str)++;
        quote_type = DOUBLE_QUOTE;
    }
    return quote_type;
}

char	*expand_if_needed(char *str, t_var_list *v)
{
	char	*expanded;

	expanded = NULL;
	if (ft_strchr(str, '$'))
	{
		expanded = expand_variable(str, v);
		if (!expanded)
			return (NULL);
		return (expanded);
	}
	return (str);
}

char 	*handle_quotes(char *str, t_var_list *v)
{
	t_quote_type quote_type;
	char *expanded;

	quote_type = remove_outer_quotes(str);
    if (quote_type == DOUBLE_QUOTE)
        expanded = expand_if_needed(str, v);
    else
        expanded = ft_strdup(str);
    return (expanded);
}

void	handle_empty_var_assignment(char **input, t_var_list *v)
{
	if (*input == NULL || **input == '\0')
	{
		add_var(&v, *input);
		return ;
	}
}

void	process_var_assigment(char **input, t_var_list *v)
{
	char	*equal_pos;
	char	*value;
	char	*prefix;
	char 	*new_input;
	char	*unquoted;
	
	handle_empty_var_assignment(input, v);
	new_input = NULL;
	equal_pos = ft_strchr(*input, '=');
	if (equal_pos)
	{
        prefix = ft_strndup(*input, (equal_pos + 1) - *input);
        value = handle_quotes(equal_pos + 1, v);
		new_input = ft_strjoin(prefix, value);
		if (new_input)
		{
			add_var(&v, new_input);
			free(prefix);
			free(new_input);
		}
	}
	else
		add_var(&v, *input);
}
