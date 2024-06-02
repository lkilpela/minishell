/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/06/02 23:07:39 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	builtin_tests(t_list *cmds)
{
	t_cmd	*first_cmd;
	
	first_cmd = (t_cmd *)cmds->content;
	if (first_cmd->command)
	{
		if (ft_strcmp(first_cmd->command, "exit") == 0)
			built_exit(first_cmd);
		if (ft_strcmp(first_cmd->command, "pwd") == 0)
			built_pwd();
		if (ft_strcmp(first_cmd->command, "env") == 0)
			built_env(0);
		if (ft_strcmp(first_cmd->command, "echo") == 0)
			built_echo(first_cmd);
		if (ft_strcmp(first_cmd->command, "export") == 0)
			built_export(first_cmd);
		if (ft_strcmp(first_cmd->command, "unset") == 0)
			built_unset(first_cmd);
		if (ft_strcmp(first_cmd->command, "cd") == 0)
			built_cd(first_cmd);
	}
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

void	clear_token_quotes(t_token_list *t)
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
	write_history(NULL); //temp
}

// line 51:  only allowing var assignment as first WORD aka command
void	minishell_loop(void)
{
	char			*input;
	int				all_good;

	while (42)
	{
		all_good = 1;
		input = readline(PROMPT);
		if (input == NULL) // ctrl + D
			built_exit(NULL);
		rl_history(input);
		if (all_good && !quote_match_check(input)) // ensure quotes are balanced
			all_good = ms_exit(RELINE, E_CODE_SYN);
		//printf(GREEN "Calling tokenizer: \n" RESET);
		if (all_good)
			ms()->tokens = new_tokenizer(input);
		//print_tokens(ms()->tokens);
		if (all_good && !near_token_errors(ms()->tokens)) // check for errors in token list
			all_good = ms_exit(RELINE, E_CODE_SYN);
		if (all_good)
		{
			ms()->commands = parser(ms()->tokens);
			init_path_dirs();
			// print_cmds(ms()->commands);
			// print_executable(ms()->commands);
			builtin_tests(ms()->commands); //temp
			// execute_commands(ms()->commands);
		}
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
