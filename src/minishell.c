/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/22 12:09:23 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds, t_var_list *v)
{
		if (ft_strcmp(cmds->simples[0]->command, "exit") == 0)
			built_exit();
		if (ft_strcmp(cmds->simples[0]->command, "pwd") == 0)
			built_pwd();
		if (ft_strcmp(cmds->simples[0]->command, "env") == 0)
			built_env(0);
		if (ft_strcmp(cmds->simples[0]->command, "echo") == 0)
			built_echo(cmds->simples[0]);
		if (ft_strcmp(cmds->simples[0]->command, "export") == 0)
			built_export(cmds->simples[0]);
		if (ft_strcmp(cmds->simples[0]->command, "unset") == 0)
			built_unset(cmds->simples[0]);
		if (ft_strcmp(cmds->simples[0]->command, "cd") == 0)
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
		add_history(input);
		t = tokenizer(input, v);
		retokenizer(&t, v);
		print_tokens(t);
		cmds = parser(t);
		if (ft_strchr(cmds->simples[0]->command, EQUAL_SIGN) != NULL) //only allowing var assignment as first WORD aka command
		{
			process_var_assignment(&input, v);
			free(input);
			print_var_list(v);
			continue ;
		}
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
