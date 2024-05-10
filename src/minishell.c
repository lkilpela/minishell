/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/10 21:05:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>

void minishell_loop()
{
	char		*input;
	t_tokenizer	t;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		printf("You entered: %s\n", input);
		add_history(input);
		init_tokenizer(&t, input);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;

	init_minishell(argc, argv, envp, &m);
	minishell_loop();
	
}
