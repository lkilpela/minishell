/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/11 19:58:41 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>


t_token *create_token(const char *value, t_token_type type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->value = ft_strdup(value);
	token->type = type;
	return (token);
}


void	tokenizer(t_tokenizer *t)
{
	t_token_list *new;

	if (!t->input)
		return (NULL);
	while (t->input)
	{
		if(t->input[t->pos] == SPACE)
			t->pos = skip_whitespaces(t->input + t->pos) - t->input;
		if (t->input[t->pos] == PIPE_CHAR || t->input[t->pos] == LESS_CHAR
			|| t->input[t->pos] == GREAT_CHAR)
		{
			new = add_node(t, t->current_token);
			if (!new)
				return ;
		}
	}
}

void	s_quote(t_tokenizer *t)
{
	
}