
#include <minishell.h>

void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	ft_free((void **)&lst->token->value);
	ft_free((void **)&lst);
}

void	free_token_list(t_token_list **lst)
{
	t_token_list	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		delone_node(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

void print_var_list(void)
{
	t_var_list	*v;

	v = ms()->var_list;
	while (v)
	{
		printf(CYAN "var_name: %s \t\t\t var_value: %s\n" RESET, v->key, v->value);
		v = v->next;
	}
}

void	print_lalloc()
{
	t_list	*lalloc;

	lalloc = *allocs();
	while (lalloc)
	{
		ft_printf("%p\n", lalloc->content);
		lalloc = lalloc->next;
	}
}

void print_last_node(void)
{
	t_var_list	*v;

	v = ms()->var_list;
    if (v == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    // Traverse the list to find the last node
    while (v->next != NULL)
    {
        v = v->next;
    }

    // Now v points to the last node
    printf(CYAN "var_name: %s \t\t\t var_value: %s\n" RESET, v->key, v->value);
}

char	*get_type_str(int e)
{
	static char	*type_str[] = {
		"WORD",
		"OP_PIPE",
		"OP_LESS",
		"OP_GREAT",
		"OP_DLESS",
		"OP_DGREAT",
		"VAR",
		"UNKNOWN"
	};

	return (type_str[e]);
}

void print_a_token(t_token_list *lst)
{
	printf("%sa_token_value: %-20s a_token_type: %s\n%s", BLUE, lst->token->value, get_type_str(lst->token->type), RESET);

}

void print_tokens(t_token_list *lst)
{
	while (lst)
	{
		print_a_token(lst);
		lst = lst->next;
	}
}


void print_last_token_node(t_token_list *t)
{
    if (t == NULL)
    {
        printf("The list is empty.\n");
        return;
    }

    // Traverse the list to find the last node
    while (t->next != NULL)
    {
        t = t->next;
    }

    // Now v points to the last node
    printf("%stoken_name: %-20s token_value: %s\n%s", BLUE, t->token->value, get_type_str(t->token->type), RESET);
}

void print_simple_cmd(t_simple_cmd *cmd) {
	if (cmd == NULL) {
		ft_printf("NULL command\n");
		return;
	}
	if (cmd->heredoc)
		ft_printf("Heredoc: %s", cmd->heredoc);
	ft_printf("Input redirection: %s\n", cmd->in_file.file);
	if (cmd->out_file.append)
		ft_printf("(APPEND) ");
	ft_printf("Output redirection: %s\n", cmd->out_file.file);
	ft_printf("Command: %s\n", cmd->command);
	ft_printf("Args (%d): ", cmd->num_of_args);
	int	i = 0;
	while (i < cmd->num_of_args)
	{
		ft_printf("<%s> ", cmd->args[i]);
		i++;
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
	while (i < cmds->num_of_cmds)
	{
		ft_printf("\e[0;32mCommand %d:\e[0m\n", i + 1);
		print_simple_cmd(cmds->simples[i]);
		i++;
	}
}
