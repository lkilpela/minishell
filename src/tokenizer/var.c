/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 13:31:02 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

void free_var(t_var *var)
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

t_var	*create_var(char *env_str)
{
	char	*equal_sign;
	t_var	*var;

	equal_sign = ft_strchr(env_str, '=');
		if (!equal_sign)
			return ;
	// create a new t_var struct
	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = ft_strndup(env_str, equal_sign - env_str);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	var->value = ft_strdup(equal_sign + 1);
	if (!var->value)
	{
		free(var->name);
		free(var);
		return (NULL);
	}
	return (var);	
}

void	add_env_var (t_var_list **lst, char *env_str)
{
	t_var_list	*node;
	t_var_list	*last;

	// create a new t_var_list node
	node = malloc(sizeof(t_var_list));
	if (!node)
		return (NULL);
	node->current_var = var;
	node->next = NULL;
	
	// add new node to the end of list
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


t_var_list *get_envp(char **envp)
{
	t_var_list *head = NULL;
	t_var_list *tail = NULL;
	t_var_list	*current_var;
	t_var	*var_node;
	char	*name;
	char	*value;
	size_t	*name_len;
	
	int i = 0;

	while (envp[i])
	{

		name_len = equal_sign - envp[i];
		
		
		current_var = create_var(name, value);
		var_node = create_var_node(current_var);
		if (!head)
			head = var_node;
		else
			tail->next = var_node;
		tail = var_node;
		i++;
	}
	return (head);
}
