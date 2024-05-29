/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 15:06:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define PERMISSION 0644

void	validate_command(t_commands *c)
{
	int i;
	char *infile;
	char *outfile;

	i = 0;
	if (i < c->num_of_cmds)
	{
		infile = c->simples[i]->in_file.file;
		outfile = c->simples[i]->out_file.file;
		if (access(infile, F_OK) == 0 )
			print_error("minishell: infile: ", ERR_FILE, NULL, 1);
		else if (access(outfile, F_OK) == 0)
			print_error("minishell: outfile: ", ERR_FILE, NULL, 1);
	}
}

void	validate_permission(t_commands *c)
{
	int	i;

	i = 0;
	while (i < c->num_of_cmds)
	{
		if (c->simples[i]->in_file.file != NULL)
		{
			c->simples[i]->in_file.fd = open(c->simples[i]->in_file.file, O_RDONLY);
			if (c->simples[i]->in_file.fd == -1)
				ft_error(WARNING, ERR_PERM, 1);
		}
		if (c->simples[i]->out_file.file != NULL)
		{
			c->simples[i]->out_file.fd = open(c->simples[i]->out_file.file,
					O_CREAT | O_WRONLY | O_TRUNC, PERMISSION);
			if (c->simples[i]->out_file.fd == -1)
				ft_error(WARNING, ERR_PERM, 1);
		}
		i++;
	}
}
