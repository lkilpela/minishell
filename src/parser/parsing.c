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

	test->token.value = ">";
	test->token.type = OP_DGREAT;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "myout";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = ">";
	test->token.type = OP_GREAT;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "test";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "<<";
	test->token.type = OP_DLESS;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "a";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "-l";
	test->token.type = WORD;
	test->next = malloc(sizeof(t_token_list));
	test = test->next;

	test->token.value = "|";
	test->token.type = OP_PIPE;
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
	while (tokens && tokens->token.type != OP_PIPE)
	{
		if (tokens->token.type >= OP_LESS && tokens->token.type <= OP_DGREAT)
		{
			tokens = tokens->next;
			if (tokens->token.type == WORD)
				tokens = tokens->next;
			continue ;
		}
		if (tokens->token.type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*heredoc(t_token_list *tokens)
{
	char	*line;
	char	*heredoc;
	char	*here_temp;
	char	*delim;

	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(0);
	heredoc = ft_calloc(1, 1);
	if (tokens->token.type != WORD)
		return (heredoc);
	delim = tokens->token.value;
	while (line)
	{
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			return (heredoc);
		}
		here_temp = ft_strdup(heredoc);
		free(heredoc);
		heredoc = ft_strjoin(here_temp, line);
		free(here_temp);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
	}
	free(line);
	return (heredoc); //no delim warning (bash: warning: here-document at line 1 delimited by end-of-file (wanted `<delimiter-value>'))
}

t_token_list	*get_redir(t_simple_cmd *simple, t_token_list *tokens)
{
	if (tokens->token.type == OP_DLESS)
	{
		tokens = tokens->next;
		simple->heredoc = heredoc(tokens);
	}
	if (tokens->token.type == OP_LESS)
	{
		if (simple->heredoc)
		{
			free(simple->heredoc);
			simple->heredoc = NULL;
		}
		tokens = tokens->next;
		if (tokens->token.type == WORD)
		{
			simple->in_file.file = tokens->token.value;
			return (tokens->next);
		}
	}
	if (tokens->token.type == OP_GREAT || tokens->token.type == OP_DGREAT)
	{
		simple->out_file.append = 0;
		if (tokens->token.type == OP_DGREAT)
			simple->out_file.append = 1;
		tokens = tokens->next;
		if (tokens->token.type == WORD)
		{
			simple->out_file.file = tokens->token.value;
			return (tokens->next);
		}
	}
	return (tokens);
}

t_simple_cmd	*simple_cmd(t_token_list **tokens)
{
	t_simple_cmd	*simple_cmd;
	int				i;

	simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	while ((*tokens) && (*tokens)->token.type != OP_PIPE)
	{
		if ((*tokens)->token.type >= OP_LESS && (*tokens)->token.type <= OP_DGREAT)
		{
			(*tokens) = get_redir(simple_cmd, *tokens);
			continue ;
		}
		if (simple_cmd->command == NULL && (*tokens)->token.type == WORD)
		{
			simple_cmd->command = (*tokens)->token.value;
			(*tokens) = (*tokens)->next;
			simple_cmd->num_of_args = count_args(*tokens);
			simple_cmd->args = ft_calloc(simple_cmd->num_of_args, sizeof(char *));
			i = 0;
			continue ;
		}
		if (simple_cmd->command != NULL && (*tokens)->token.type == WORD)
			simple_cmd->args[i++] = (*tokens)->token.value;
		(*tokens) = (*tokens)->next;
	}
	return (simple_cmd);
}

int	count_cmd(t_token_list *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->token.type == OP_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

t_commands	*parser(t_token_list *tokens)
{
	t_commands	*cmds;
	int	i;

	cmds = ft_calloc(1, sizeof(t_commands));
	cmds->simples = ft_calloc(count_cmd(tokens), sizeof(t_simple_cmd *));
	i = 0;
	while (tokens)
	{
		cmds->simples[i++] = simple_cmd(&tokens);
		if (tokens)
			tokens = tokens->next;
	}
	return (cmds);
}

void print_simple_cmd(t_simple_cmd *cmd) {
	if (cmd == NULL) {
		ft_printf("NULL command\n");
		return;
	}
	if (cmd->heredoc)
		ft_printf("Heredoc: %s\n", cmd->heredoc);
	ft_printf("Input redirection: %s\n", cmd->in_file.file);
	if (cmd->out_file.append)
		ft_printf("(APPEND) ");
	ft_printf("Output redirection: %s\n", cmd->out_file.file);
	ft_printf("Command: %s\n", cmd->command);
	ft_printf("Args (%d): ", cmd->num_of_args);
	for (int i = 0; i < cmd->num_of_args; i++) {
		ft_printf("\"%s\" ", cmd->args[i]);
	}
	ft_printf("\n");
}

void	print_commands(t_commands *cmds)
{
	int	i = 0;

	if (cmds == NULL)
	{
		ft_printf("NULL commands structure\n");
		return;
	}
	while (cmds->simples && cmds->simples[i])
	{
		ft_printf("\e[0;32mCommand %d:\e[0m\n", i + 1);
		print_simple_cmd(cmds->simples[i]);
		i++;
	}
}

// int	main()
// {
// 	t_token_list *test = init_test();
// 	t_commands *cmds = parser(test);
// 	print_commands(cmds);

// }