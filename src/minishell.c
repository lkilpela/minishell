/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/15 14:25:22 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <parser.h>

void minishell_loop()
{
	char		*input;
	//t_tokenizer	t;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		add_history(input);
		//init_tokenizer(&t, input);
		t_token_list *lst = tokenize_input(input);
		print_tokens(lst);
		print_commands(parser(lst));
		free_list(&lst);
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
	minishell_loop();
}
