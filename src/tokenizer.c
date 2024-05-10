/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/10 22:31:03 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>


void	split_on_space(t_tokenizer *t)
{
	
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