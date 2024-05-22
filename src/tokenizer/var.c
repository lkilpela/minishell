/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 18:13:41 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void extract_var(char *str, char **key, char **value)
{
	char	*equal_sign;

	*key = NULL;
	*value = NULL;
	equal_sign = ft_strchr(str, EQUAL_SIGN);
	if (!equal_sign)
		return ;
	*key = ft_strndup(str, equal_sign - str);
	if (!*key)
		return ;
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
		return ;
}

// create a new t_var_list node
static t_var_list *create_var_node(char *key, char *value)
{
	t_var_list	*node;

	node = ft_calloc(1, sizeof(t_var_list));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	return (node);
}

t_var_list	*var_get_last(void)
{
	t_var_list	*last;

	last = ms()->var_list;
	while (last->next)
		last = last->next;
	return (last);
}

// add new node to the end of list
static void	add_var_to_list(t_var_list *node)
{
	t_var_list	*last;

	if (ms()->var_list == NULL)
		ms()->var_list = node;
	else
	{
		last = var_get_last();
		node->previous = last;
		last->next = node;
	}
}

void	add_var(char *str)
{
	t_var_list	*node;
	t_var_list	*vars;
	char		*key;
	char		*value;

	extract_var(str, &key, &value);
	if (!key || !value)
		return ;
	vars = ms()->var_list;
	while (vars) // if the name is existed, update it with new one
	{
		if(ft_strcmp(vars->key, key) == 0)
		{
			free(vars->key);
			free(vars->value);
			vars->key = key;
			vars->value = value;
			return ;
		}
		vars = vars->next;
	}
	node = create_var_node(key, value);
	if (!node)
		return;
	add_var_to_list(node);
}

static void	handle_empty_var_assignment(char **input)
{
	if (*input == NULL || **input == '\0')
	{
		add_var(*input);
		return ;
	}
}

void	process_var_assignment(char **input)
{
	char			*equal_pos;
	char			*value;
	char			*prefix;
	char 			*new_input;

	handle_empty_var_assignment(input);
	new_input = NULL;
	equal_pos = ft_strchr(*input, EQUAL_SIGN);
	if (equal_pos)
	{
		prefix = ft_strndup(*input, (equal_pos + 1) - *input);
		value = check_quotes_and_expand(equal_pos + 1);
		new_input = ft_strjoin(prefix, value);
		if (new_input)
		{
			add_var(new_input);
			free(prefix);
			free(new_input);
		}
	}
	else
		add_var(*input);
	print_last_node();
}

t_var_list	*get_envp(char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		add_var(envp[i]);
		i++;
	}
	return (ms()->var_list);
}

void	var_remove(char *key)
{
	t_var_list	*vars;

	vars = ms()->var_list;
	if (!key)
		return ;
	while (vars)
	{
		if (ft_strcmp(key, vars->key) == 0)
		{
			if (vars->previous)
				vars->previous->next = vars->next;
			if (vars->next)
				vars->next->previous = vars->previous;
			free(vars);
			vars = NULL;
			return ;
		}
		vars = vars->next;
	}
}
