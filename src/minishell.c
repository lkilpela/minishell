/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/10 15:41:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>

void minishell_loop()
{
	char	*prompt;

	while (42)
	{
		prompt = readline(PROMPT);
		printf("You entered: %s\n", prompt);
		free(prompt);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;

	init_minishell(argc, argv, envp, &m);
	minishell_loop();
}

/*int main(void)
{
	char *line;
	t_token_list *tok;

	while (42)
	{
		line = readline("Minishell:<");
		tok = lexer(line);
		while (tok)
		{
			printf("<type: '%c' str: '%s'\n", tok->type, tok->str);
			tok = tok->next;
		}
		// printf("%s\n", line);
		free(line);
	}
	return (0);
}*/