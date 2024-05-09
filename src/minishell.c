/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/09 22:15:42 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(void)
{
	char *line;
	t_tok_list *tok;

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
}