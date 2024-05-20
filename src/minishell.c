/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/20 15:11:16 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds, t_var_list *v)
{
		built_echo(cmds->simples[0]);
		if (ft_strcmp(cmds->simples[0]->command, "pwd") == 0)
			built_pwd(v);
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
		t = tokenizer(input, v);
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
