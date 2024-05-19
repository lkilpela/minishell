/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/19 14:02:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void minishell_loop(t_var_list *v)
{
	char			*input;
	t_token_list	*t;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		add_history(input);
		t = tokenizer(input, v);
		//print_var_list(v);
		print_tokens(t);
		//print_commands(parser(lst));
		//free_var_list(v);
		free_token_list(&t);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	t_var_list *v;

	init_minishell(argc, argv, envp, &m);
	v = get_envp(envp);
	minishell_loop(v);
}
