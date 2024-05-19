/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 00:20:22 by aklein           ###   ########.fr       */
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
		if (!input || ft_strcmp(input, "exit") == 0)
			break ;
		add_history(input);
		if (ft_strchr(input, EQUAL_SIGN) != NULL)
		{
			process_var_assignment(&input, v);
			free(input);
			continue ;
		}
		t = tokenizer(input, v);
		retokenizer(&t, v);
		print_tokens(t);
		cmds = parser(t);
		builtin_tests(cmds, v);
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
	read_history("history_file.txt"); // for testing
	minishell_loop(v);
	write_history("history_file.txt");  // for testing
}
