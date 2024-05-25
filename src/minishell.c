/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/27 06:44:50 by lkilpela         ###   ########.fr       */
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
	char	*start;
	char	*new_val;
	size_t	len;
	
	len = ft_strlen(val);
	start = val;
	while (*val)
	{
		if (is_quote(*val))
		{
			handle_quotes(&val);
			break ;
		}
		val++;
	}
	if (ft_strlen(start) != len)
	{
		new_val = ft_safe_strdup(start);
		ft_free((void **)&start);
		return (new_val);
	}
	return (start);
}

void	clear_quotes(t_token_list *t)
{
	char	*val;

	while (t)
	{
		val = t->token->value;
		t->token->value = handle_node_quotes(val);
		t = t->next;
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
		if (input == NULL) // ctrl + D
			built_exit(NULL);
		add_history(input);
		if (!quote_match_check(input)) // ensure quotes are balanced
		{
			ft_error(WARNING, ERR_QUOTES, 1);
			ft_free((void **)&input);
			continue ;
		}
		t = tokenizer(input);
		retokenizer(&t);
		clear_quotes(t);
		if (!near_token_errors(t)) // check for errors in token list
		{
			ft_free((void **)&input);
			continue ;
		}
		printf("final token_list: \n");
		print_tokens(t);
		cmds = parser(t);
		if (ft_strchr(cmds->simples[0]->command, EQUAL_SIGN) != NULL) // local var assignment
		{
			process_var_assignment(&input);
			ft_free((void **)&input);
			print_var_list();
			continue ;
		}
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
	minishell_loop();
}
