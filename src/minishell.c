/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/20 10:42:07 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds, t_var_list *v)
{
		built_echo(cmds->simples[0]);
		if (strcmp(cmds->simples[0]->command, "pwd") == 0)
			built_pwd(v);
}

void minishell_loop(t_var_list *v)
{
	char			*input;
	t_token_list	*t;
	t_commands		*cmds;

	while (42)
	{
		t = tokenizer(input, v);
		//print_var_list(v);
		print_tokens(t);
		cmds = parser(t);
		// print_commands(parser(t));
		builtin_tests(cmds, v);
		//free_var_list(v);
		free_token_list(&t);
		free(input);
	}
}
t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

int main(int argc, char **argv, char **envp)
{
	t_var_list *v;

	init_minishell(argc, argv, envp);
	v = get_envp(envp);
	manage_history();
	minishell_loop(v);
}
