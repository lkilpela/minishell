/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/09 22:22:27 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>


int main(int argc, char **argv, char **envp)
{
	
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