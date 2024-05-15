/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 12:40:33 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tokenizer.h>

t_var	*expand_variables(t_token *token)
{
	t_var	*var;
	char	*env_value;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	if (token->type == VAR)
	{
		// store token.value to var.name
		var->name = ft_strdup(token->value);
		if (!var->name)
		{
			free(var);
			return (NULL);
		}
		env_value = getenv(token->value);
		if (env_value)
		{
			var->value = ft_strdup(env_value);
			if (!var->value)
			{
				free(var->name);
				free(var);
				return (NULL);
			}
		}
		else
			var->value = NULL;
	}
	return (var);
}

t_envp	*get_a_var(char *name, char *value)
{
	t_envp	*a_var;

	a_var = malloc(sizeof(t_envp));
	if (!a_var)
		return (NULL);
	a_var->name = ft_strdup(name);
	if (!a_var->name)
	{
		free(var);
		return (NULL);
	}
	a_var->value = ft_strdup(value);
	if (!a_var->value)
	{
		free(var->name);
		free(var);
		return (NULL);
	}
}

t_var *create_var_node(t_envp *var)
{
	t_var	*var_node;

	var_node = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var_node->name = var;
	var_node->value = NULL;
	return (var);
}

t_envp *get_envp(char **envp)
{
	t_envp *head = NULL;
	t_envp *tail = NULL;
	t_envp	*var;
	t_var	*var_node;
	char	*name;
	char	*value;
	size_t	*name_len;
	char	*equal_sign;
	int i = 0;

	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		if (!equal_sign)
			continue;
		name_len = equal_sign - envp[i];
		name = ft_strndup(envp[i], name_len);
		value = ft_strdup(equal_sign + 1);
		var = get_a_var(name, value);
		var_node = create_var_node(var);
		if (!head)
			head = var_node;
		else
			tail->next = var_node;
		tail = var_node;
		i++;
	}
	return (head);
}