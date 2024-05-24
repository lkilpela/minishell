
#include <minishell.h>

void	free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}

void free_var_list(void)
{
	t_var_list *node;
	t_var_list *next;

	node = ms()->var_list;
	while (node)
	{
		if (node->key)
			free(node->key);
		if (node->value)
			free(node->value);
		next = node->next;
		free(node);
		node = next;
	}
}
void	delone_node(t_token_list *lst)
{
	if (!lst)
		return ;
	free(lst->token->value);
	free(lst);
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
	printf(BLUE "a_token_value: %-20s a_token_type: %s\n" RESET, lst->token->value, get_type_str(lst->token->type));

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
    printf(BLUE "token_name: %-20s token_value: %s\n" RESET, t->token->value, get_type_str(t->token->type));
}