/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/29 23:27:28 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_commands *cmds)
{
	if (ft_strcmp(cmds->simples[0]->command, "exit") == 0)
		built_exit(cmds->simples[0]);
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
		built_cd(cmds->simples[0]);
}

void	handle_quotes(char **val)
{
	char	quote;
	
	quote = **val;
	ft_memmove(*val, *val + 1, ft_strlen(*val));
	while (**val)
	{
		if (**val == quote)
		{
			ft_memmove(*val, *val + 1, ft_strlen(*val));
			break ;
		}
		(*val)++;
	}
}

char	*handle_node_quotes(char *val)
{
	char	*current;
	char	*new_val;
	size_t	len;
	
	len = ft_strlen(val);
	current = val;
	while (*current)
	{
		if (is_quote(*current))
			handle_quotes(&current);
		else
			current++;
	}
	if (ft_strlen(val) != len)
	{
		new_val = ft_safe_strdup(val);
		ft_free((void **)&val);
		return (new_val);
	}
	return (val);
}

void	clear_quotes(t_token_list *t)
{
	char	*val;

	while (t)
	{
		val = t->value;
		t->value = handle_node_quotes(val);
		t = t->next;
	}
}

void	rl_history(char *input)
{
	static char	*last = NULL;

	if (!last || ft_strcmp(last, input) != 0)
		add_history(input);
	ft_free((void **)&last);
	last = ft_safe_strdup(input);
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
		if (input == NULL) // ctrl + D
			built_exit(NULL);
		rl_history(input);
		if (!quote_match_check(input)) // ensure quotes are balanced
		{
			ft_error(WARNING, ERR_QUOTES, 1);
			ft_free((void **)&input);
			continue ;
		}
		printf(GREEN "Calling tokenizer: \n" RESET);
		t = new_tokenizer(input);
		print_tokens(t);
		printf(GREEN "expander: \n" RESET);
		exp_and_insert(&t);
		print_tokens(t);
		if (!near_token_errors(t)) // check for errors in token list
		{
			ft_free((void **)&input);
			continue ;
		}
		clear_quotes(t);
		printf("After quote_clear: \n");
		print_tokens(t);
		cmds = parser(t);
		init_path_dirs();
		//print_executable(cmds);
		//setup_pipes(cmds);
		validate_arguments(cmds);
		execute_commands(cmds);
		builtin_tests(cmds);
		ft_free((void **)&input);
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
	read_history(NULL);
	minishell_loop();
}
