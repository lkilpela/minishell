/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:45:43 by aklein            #+#    #+#             */
/*   Updated: 2024/05/09 17:16:28 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//example list of t_tok elements with tokens for the input "ls -l | cat -e"

#include <minishell.h>
#include <parser.h>

t_tok_list	*init_test()
{
	t_tok_list	*test;
	test = malloc(sizeof(t_tok_list));
	t_tok_list	*ptr = test;
	test->str = "ls";
	test->type = WORD;
	test->next = malloc(sizeof(t_tok_list));
	test = test->next;
	test->str = "-l";
	test->type = WORD;
	test->next = malloc(sizeof(t_tok_list));
	test = test->next;
	test->str = "|";
	test->type = PIPE;
	test->next = malloc(sizeof(t_tok_list));
	test = test->next;
	test->str = "cat";
	test->type = WORD;
	test->next = malloc(sizeof(t_tok_list));
	test = test->next;
	test->str = "-e";
	test->type = WORD;
	test->next = NULL;
	return (ptr);
}

char	*handle_dollar(char *str)
{
	char	*env;

	env = getenv(str);
	return (env);

}

int	count_args(t_tok_list *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != PIPE);
	{
		count++;
		tokens = tokens->next;
	}
}

void	parser(t_tok_list *tokens)
{
	t_commands		*commands;
	t_simple_cmd	*simple_cmd;
	t_tok_list		*ptr;
	int	i;

	commands = ft_calloc(1, sizeof(t_commands));
	commands->commands = ft_calloc(10, sizeof(t_simple_cmd));
	i = 0;
	ptr = tokens;
	while (ptr)
	{
		simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
		if (ptr->type == DOLLAR)
		{
			ptr = ptr->next;
			simple_cmd->command = handle_dollar(ptr->str);
		}
		else
			simple_cmd->command = ptr->str;
		simple_cmd->num_of_args = count_args(ptr);
		simple_cmd->args = ft_calloc(simple_cmd->num_of_args, sizeof(char *));
		ptr = ptr->next;
		while (ptr && (ptr->type == WORD || ptr->type == DOLLAR))
		{
			if (ptr->type == DOLLAR)
			{
				ptr = ptr->next;
				if (ptr->type == WORD)
					simple_cmd->args[i] = handle_dollar(ptr->str);
			}
			else
				simple_cmd->args[i] = ptr->str;
			i++;
			ptr = ptr->next;
		}
		commands->commands[i] = simple_cmd;
		i++;
	}
}

int	main()
{
	t_tok_list *test = init_test();
	parser(test);
}
