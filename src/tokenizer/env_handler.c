/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 01:58:47 by aklein            #+#    #+#             */
/*   Updated: 2024/05/23 14:12:06 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	env_array_size(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

char	**env_array_dup(char **envp, int size, int cut)
{
	char	**env_copy;
	int		i;

	if (size < 0)
		return (NULL);
	env_copy = ft_calloc((size + 1), sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < size && i < env_array_size(envp))
	{
		if (cut == -1 || i < cut)
			env_copy[i] = ft_strdup(envp[i]);
		else
			env_copy[i] = ft_strdup(envp[i + 1]);
		if (!env_copy[i])
		{
			while (i--)
				free(env_copy[i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	return (env_copy);
}

void	env_free_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	env_key_len(char *env)
{
	int	len;

	len = 0;
	while (*env && *env != '=')
	{
		env++;
		len++;
	}
	return (len);
}

int	env_is_env(char *env)
{
	while (*env)
	{
		if (*env == EQUAL_SIGN)
			return (1);
		env++;
	}
	return (0);
}

int	env_exists(char *keyval)
{
	int		len;
	char	**envp;
	char	*key;
	int		i;

	envp = ms()->envp;
	i = 0;
	while (envp[i])
	{
		len = env_key_len(envp[i]);
		key = ft_substr(keyval, 0, len);
		if (ft_strnstr(envp[i], key, len))
		{
			free(key);
			return (i);
		}
		i++;
	}
	return (-1);
}

void	env_remove(char *keyval)
{
	int		i;
	int		size;
	char	**new_envp;

	i = env_exists(keyval);
	if (i != -1)
	{
		size = env_array_size(ms()->envp);
		ft_printf("removed '%s'\n", ms()->envp[i]);
		new_envp = env_array_dup(ms()->envp, size - 1, i);
		ms()->envp = new_envp;
	}
}

void	env_add(char *keyval)
{
	int		i;
	char	**new_envp;
	int		size;

	i = env_exists(keyval);
	if (i != -1)
	{
		ft_printf("changed '%s' ", ms()->envp[i]);
		free(ms()->envp[i]);
		ms()->envp[i] = ft_strdup(keyval);
		ft_printf("to '%s'\n", ms()->envp[i]);
	}
	else
	{
		size = env_array_size(ms()->envp);
		new_envp = env_array_dup(ms()->envp, size + 1, -1);
		new_envp[size] = ft_strdup(keyval);
		env_free_array(ms()->envp);
		ms()->envp = new_envp;
		ft_printf("added '%s' to envs\n", ms()->envp[size]);
	}
}
