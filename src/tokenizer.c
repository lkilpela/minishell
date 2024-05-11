/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:09:48 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/11 20:48:36 by lkilpela         ###   ########.fr       */
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
void tokenizer()
{
	t_token_list 	*token_list;
	t_token_list	*new;

	token_list = NULL;
	new = create_token(PIPE_CHAR, PIPE);
	add_node(&token_list, new);
	new = create_token(LESS_CHAR, LESS);
	add_node(&token_list, new);
	printf("Tokens:\n");
    print_tokens(token_list);
	free_list(token_list);
}



void	tokenizer_input(t_tokenizer *t)
{
	t_token_list *new;

	new = NULL;
	if (!t->input)
		return (NULL);
}

/*void	s_quote(t_tokenizer *t)
{
	
}*/