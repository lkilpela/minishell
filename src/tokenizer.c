/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/13 14:21:40 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>

t_token_type get_token_type(char *str)
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
	else
		return (WORD);
}

int get_token_len(char *str)
{
	int		len;
	char	*end;

	if (is_quote(*str))
	{
		len = len_inquote(str);
		str++;
	}
	else if (is_double_operator(str))
	{
		len = 2;
	}
	else
	{
		end = find_token_end(str);
		len = end - str;
	}
	return (len);
}

t_token	create_a_token(char *str)
{
	t_token	a_token;
	int		len;

	init_token(&a_token);
	len = get_token_len(str);
	a_token.type = get_token_type(str);
	a_token.value = ft_strndup(str, len);
	return (a_token);
}

t_token_list	*create_new_node(char *str)
{
	t_token_list *lst;

	lst = malloc(sizeof(t_token_list));
	if (!lst)
		return (NULL);
	init_token_list(lst);
	lst->token = create_a_token(str);
	return (lst);	
}
t_token_list *create_token_list(char **str, int count)
{
	t_token_list	*lst;
	t_token_list	*temp;
	t_token_list	*new;
	int				i;

	if (count <= 0)
		return (NULL);
	lst = create_new_node(str[0]);
	if (!lst)
		return (NULL);
	temp = lst;
	i = 1;
	while (i < count)
	{
		new = create_new_node(str[i]);
		if (!new)
			return (NULL);
		temp->next = new;
		temp = new;
		i++;
	}
	temp->next = NULL;
	return (lst);
}
t_token_list	**create_token_list(char *str)
{
	int				number_token;
	char			**tokens;
	t_token_list	*lst;

	number_token = count_tokens(str);
	tokens = split_input(str);
	if (!tokens)
		return (NULL);
	lst = 
}