#include <minishell.h>
#include <tokenizer.h>
#include <parser.h>

t_token_list	*init_test()
{
	t_token_list	*test;
	t_token_list	*ptr;
	test = malloc(sizeof(t_token_list));
	ptr = test;
	test->token.value = "ls";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;
	test->token.value = "-l";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;
	test->token.value = "|";
	test->token.type = PIPE;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;
	test->token.value = "cat";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;
	test->token.value = "-e";
	test->token.type = WORD;
	test->next = NULL;
	return (ptr);
}

int	count_args(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token.type != PIPE)
	{
		if (tokens->token.type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_commands	*parser(t_token_list *tokens)
{
	t_commands		*commands;
	t_simple_cmd	*simple_cmd;
	int	i;
	int	cmd_i;

	commands = ft_calloc(1, sizeof(t_commands));
	commands->commands = ft_calloc(10, sizeof(t_simple_cmd *));
	cmd_i = 0;
	while (tokens)
	{
		simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
		if (tokens->token.type == PIPE)
		{
			tokens = tokens->next;
			continue ;
		}
		else
			simple_cmd->command = tokens->token.value;
		tokens = tokens->next;
		simple_cmd->num_of_args = count_args(tokens);
		simple_cmd->args = ft_calloc(simple_cmd->num_of_args, sizeof(char *));
		i = 0;
		while (tokens && (tokens->token.type == WORD))
		{
			simple_cmd->args[i] = tokens->token.value;
			i++;
			tokens = tokens->next;
		}
		commands->commands[cmd_i] = simple_cmd;
		cmd_i++;
	}
	return (commands);
}

void print_simple_cmd(t_simple_cmd *cmd) {
	if (cmd == NULL) {
		ft_printf("NULL command\n");
		return;
	}

	ft_printf("Command: %s\n", cmd->command);
	ft_printf("Args (%d): ", cmd->num_of_args);
	for (int i = 0; i < cmd->num_of_args; i++) {
		ft_printf("\"%s\" ", cmd->args[i]);
	}
	ft_printf("\n");
}

void print_commands(t_commands *cmds) {
	int i = 0;

	if (cmds == NULL) {
		ft_printf("NULL commands structure\n");
		return;
	}
	if (cmds->in_file)
		ft_printf("Input redirection: %s\n", cmds->in_file);
	if (cmds->out_file)
		ft_printf("Output redirection: %s\n", cmds->out_file);
	while (cmds->commands && cmds->commands[i]) {
		ft_printf("Command %d:\n", i + 1);
		print_simple_cmd(cmds->commands[i]);
		i++;
	}
}

int	main()
{
	t_token_list *test = init_test();
	t_commands *cmds = parser(test);
	print_commands(cmds);

}
