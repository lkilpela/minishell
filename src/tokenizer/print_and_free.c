
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

static void free_var(t_var *var)
{
	if (var)
	{
		free(var->name);
		free(var->value);
		free(var);
	}
}

void free_var_list(t_var_list *list)
{
	t_var_list *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_var(tmp->current_var);
		free(tmp);
	}
}
static void	delone_node(t_token_list *lst)
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

void print_var_list(t_var_list *v)
{
	while (v)
	{
		printf(CYAN "Name: %s \t\t\t\t Value: %s\n" RESET, v->current_var->name, v->current_var->value);
		v = v->next;
	}
}

void print_last_node(t_var_list *v)
{
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
    printf(CYAN "Name: %s \t\t\t\t Value: %s\n" RESET, v->current_var->name, v->current_var->value);
}

