/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/16 14:40:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

char *remove_quotes(char *str)
{
	char *p = str;
	char *q = str;
	while (*p)
	{
		if (*p != '\"')
			*q++ = *p;
		p++;
	}
	*q = '\0';
	return (str);
}

static char *lookup_var(char *var_name, t_var_list *v)
{
	while (v)
	{
		if (ft_strcmp(v->current_var->name, var_name) == 0)
			return (ft_strdup(v->current_var->value));
		v = v->next;
	}
	return (NULL);
}

char *expand_variable(char *str, t_var_list *v)
{
	char	*start;
	char	*prefix;
	char	*end;
	char 	*expanded_str;
	char	*temp;
	char	*var_name;
	char	*var_value;

	printf("input: %s\n", str);
	start = ft_strchr(str, '$');
	end = skip_variable(start);
	prefix = ft_strndup(str, start - str);
	var_name = ft_strndup(start + 1, end - start - 1);
	printf("var_name: %s\n", var_name);
	var_value = lookup_var(var_name, v);
	printf("var_value: %s\n",var_value);
	if (var_value)
	{
		temp = ft_strjoin(prefix, var_value);
		expanded_str = ft_strjoin(temp, end);
		free(temp);
	}
	else	
		expanded_str = ft_strdup(str);
	free(prefix);
	return (expanded_str);
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

static void extract_var(char *str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return ;
	*name = ft_strndup(str, equal_sign - str);
	*value = ft_strdup(equal_sign + 1);
	*value = remove_quotes(*value);
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

static void	add_var(t_var_list **lst, char *str)
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
	while (v)
	{
		if(ft_strcmp(v->current_var->name, name) == 0)
		{
			free(v->current_var->name);
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

void print_envp(t_var_list *lst)
{
	while (lst)
	{
		printf("Name: %s \t\t\t\t Value: %s\n", lst->current_var->name, lst->current_var->value);
		lst = lst->next;
	}
}
