/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:49:39 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 10:40:38 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define FILE_PATH "ms/history_file.txt"

void	read_history_from_file(void)
{
	int		fd;
	char	*line;

	line = NULL;
	if (access(FILE_PATH, F_OK) != -1)
	{
		fd = open(FILE_PATH, O_RDONLY);
		if (fd == -1)
			return ;
	}
	while (line = get_next_line(fd) != NULL)
	{
		add_history(line);
		free(line);
	}
	close(fd);
}

void save_history(void)
{
	char	*input;
	int		fd;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		add_history(input);
		fd = open(FILE_PATH, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return ;
		write (fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		close (fd);
	}
}

void	manage_history(void)
{
	read_history_from_file();
	save_history();
}