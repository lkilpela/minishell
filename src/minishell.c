/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/23 14:50:15 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds)
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
		built_cd(cmds->simples[0]->num_of_args, cmds->simples[0]->args);
		ft_printf("new pwd: %s\n", getcwd(NULL, 0));
	}
}

// line 51:  only allowing var assignment as first WORD aka command
void	minishell_loop(void)
{
	char			*input;
	t_token_list	*t;
	t_commands		*cmds;

	while (42)
	{
		input = readline(PROMPT);
		add_history(input);
		t = tokenizer(input);
		retokenizer(&t);
		cmds = parser(t);
		if (ft_strchr(cmds->simples[0]->command, EQUAL_SIGN) != NULL)
		{
			process_var_assignment(&input);
			free(input);
			print_var_list();
			continue ;
		}
		builtin_tests(cmds);
		free(input);
	}
}

t_ms	*ms(void)
{
	static t_ms	ms;

	return (&ms);
}

int	main(int argc, char **argv, char **envp)
{
	init_minishell(argc, argv, envp);
	minishell_loop();
}
