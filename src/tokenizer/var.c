/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 14:14:35 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void extract_var(char *str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return ;
	*name = ft_strndup(str, equal_sign - str);
	if (!*name)
		return ;
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
		return ;
	//*value = remove_outer_quotes(*value);
}

// create a new t_var struct
static t_var	*create_var(char *str)
{
	t_var	*var;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	extract_var(str, &name, &value);
	if (!name || !value)
		return (NULL);
	var = malloc(sizeof(t_var));
	if (!var)
	{
		free(name);
		free(value);
		return (NULL);
	}
	var->name = name;
	var->value = value;
	return (var);	
}

// create a new t_var_list node
static t_var_list *create_var_node(char *str)
{
	t_var_list	*node;
	
	node = malloc(sizeof(t_var_list));
	if (!node)
		return (NULL);
	node->current_var = create_var(str);
	if (!node->current_var)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

// add new node to the end of list
static void	add_var_to_list(t_var_list **lst, t_var_list *node)
{
	t_var_list	*last;

	if (*lst == NULL)
		*lst = node;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = node;
	}
}

void	add_var(t_var_list **lst, char *str)
{
	t_var_list	*node;
	t_var_list	*v;
	char		*name;
	char		*value;

	name = NULL;
	value = NULL;
	extract_var(str, &name, &value);
	if (!name || !value)
		return ;
	v = *lst;
	while (v) // if the name is existed, update it with new one
	{
		if(ft_strcmp(v->current_var->name, name) == 0)
		{
			free(v->current_var->name);
			free(v->current_var->value);
			v->current_var->name = name;
			v->current_var->value = value;
			return ;
		}
		v = v->next;
	}
	node = create_var_node(str);
	if (!node)
		return;
	add_var_to_list(lst, node);
	free(name);
	free(value);
}

t_var_list *get_envp(char **envp)
{
	t_var_list	*lst;
	int			i;

	lst = NULL;
	i = 0;
	while (envp[i])
	{
		add_var(&lst, envp[i]);
		i++;
	}
	return (lst);
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
