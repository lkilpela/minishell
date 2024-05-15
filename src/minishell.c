/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/15 21:37:08 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <parser.h>

void minishell_loop(t_var_list *lst)
{
	char			*input;
	//t_token_list	*lst;
	//t_tokenizer	t;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		add_history(input);
		//init_tokenizer(&t, input);
		//lst = tokenize_input(input);
		//print_tokens(lst);
		//print_commands(parser(lst));
		//free_list(&lst);
		char *temp = expand_variable(input, lst);
		printf("expanded_str: %s\n", temp);
		free(temp);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	t_var_list *lst;

	init_minishell(argc, argv, envp, &m);
	lst = get_envp(envp);
	print_envp(lst);
	free_var_list(lst);
	minishell_loop(lst);
}
