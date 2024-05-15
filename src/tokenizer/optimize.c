/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 15:59:55 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char *lookup_var(char *var_name, t_var_list *v)
{
	while (v)
	{
		if (ft_strcmp(v->current_var->name, var_name) == 0)
			return (ft_strdup(v->current_var->value));
		v = v->next;
	}
	return (NULL);
}

char *expand_variable(char *str, t_var_list *v)
{
	char	*end;
	char	*var_name;
	char	*var_value;
	char 	*expanded_str;

	end = skip_variable(str);
	var_name = ft_strndup(str + 1, end - str - 1);
	var_value = lookup_var(var_name, v);
	if (var_value)
	{
		expanded_str = ft_strjoin(var_value, end);
		free(var_value);
		return (expanded_str);
	}
	return (ft_strdup(str));
}
char *next_token(char *str)
{
	while (*str)
	{
		if (is_whitespace(*str))
			str = skip_whitespaces(str);
		else if (is_word(*str))
			str = skip_word(str);
		else if (is_operator(*str))
			str = skip_op(str);
		else if (is_quote(*str))
			str = skip_quote(str);
		else if (*str == '$')
			str = skip_variable(str);
		else
			break;
	}
	return (str);
}

int get_token_len(char *str, t_var_list *v)
{
	char	*end;
	int		len;

	
	len = end - str;
	if (is_quote(*str))
		len -= 2;
	else if (*str == '$')
	{
		if(*(str + 1) == '?')
			len = 2;
		else
			len -= 1;
	}
	return (len);
}

t_token_type	get_token_type(char *str)
{
	if (*str == '\'')
		return (S_QUOTE);
	else if (*str == '\"')
		return (D_QUOTE);
	else if (ft_strcmp(str, "<<") == 0)
		return (OP_DLESS);
	else if (ft_strcmp(str, ">>") == 0)
		return (OP_DGREAT);
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

t_token	create_token(char *str)
{
	t_token	a_token;
	char	*s;
	int		len;

	s = str;
	len = get_token_len(str);
	if (is_quote(*str) || *str == '$')
		s++;
	a_token.value = ft_strndup(s, len);
	a_token.type = get_token_type(str);
	return (a_token);
}

t_token_list	*tokenizer(char **str)
{
	
}