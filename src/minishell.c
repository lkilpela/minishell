/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/20 00:01:18 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds, t_var_list *v)
{
		built_echo(cmds->simples[0]);
		if (strcmp(cmds->simples[0]->command, "pwd") == 0)
			built_pwd();
		if (strcmp(cmds->simples[0]->command, "cd") == 0)
		{
			ft_printf("old pwd: %s\n", getcwd(NULL, 0));
			built_cd(cmds->simples[0]->num_of_args, cmds->simples[0]->args, v);
			ft_printf("new pwd: %s\n", getcwd(NULL, 0));
		}
}

void minishell_loop(t_var_list *v)
{
	char			*input;
	t_token_list	*t;
	t_commands		*cmds;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		add_history(input);
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
	built_cd(0, NULL, v); //set cwd to home
	minishell_loop(v);
}
