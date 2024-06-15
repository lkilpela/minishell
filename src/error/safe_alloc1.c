/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:31:25 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/15 22:36:26 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_safe_calloc(size_t count, size_t size)
{
	void	*alloc;

	alloc = ft_calloc(count, size);
	if (!alloc)
		ft_error(EXIT_FAILURE);
	add_to_lal(alloc);
	return (alloc);
}

char	**ft_safe_split(const char *s, char c)
{
	char	**str_arr;
	int		i;

	i = 0;
	str_arr = ft_split(s, c);
	if (!str_arr)
		ft_error(EXIT_FAILURE);
	while (str_arr[i])
	{
		add_to_lal((void *)str_arr[i]);
		i++;
	}
	add_to_lal((void *)str_arr);
	return (str_arr);
}

char	*safe_getcwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		if (errno != ENOENT)
			ft_error(EXIT_FAILURE);
		print_error(ERR_CD1, "getcwd", ERR_CD2, 1);
		return (NULL);
	}
	add_to_lal((void *)pwd);
	return (pwd);
}

void	safe_pipe(int *pipedes)
{
	if (pipe(pipedes) == -1)
		ft_error(EXIT_FAILURE);
}

int	safe_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(EXIT_FAILURE);
	return (pid);
}
