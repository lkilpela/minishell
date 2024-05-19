/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:04:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 14:36:43 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void init_minishell(int argc, char **argv, char **envp)
{
	ms()->argc = argc;
	ms()->argv = argv;
	ms()->envp = envp;
	ms()->paths = NULL;
}

/*void init_tokenizer(t_tokenizer *t, char *input)
{
	t->input = input;
	t->pos = 0;
	init_token(&(t->current_token));	
	init_token_list(t->tokens);
}*/

/*void init_var(t_var_array *v)
{
	v->size = 0;
	v->vars = NULL;
}*/