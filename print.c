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