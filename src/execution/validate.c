/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 22:47:23 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define PERMISSION 0644

void validate_redir(t_redir *infile, t_redir *outfile)
{
	/*if (access(infile->file, F_OK) == -1)
		print_error("minishell", infile->file, ERR_FILE, 0);
	else if (access(outfile->file, F_OK) == -1)
		print_error("minishell", outfile->file, ERR_FILE, 0);*/
	if (infile->file)
	{
		infile->fd = open(infile->file, O_RDONLY);
		if (infile->fd == -1)
		{
			print_error("minishell", infile->file, strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
	}
	if (outfile->file)
	{
		outfile->fd = open(outfile->file,
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSION);
		if (outfile->fd == -1)
		{
			print_error("minishell", outfile->file, strerror(errno), 1);
			exit(EXIT_FAILURE);
		}
	}
}

void	validate_arguments(t_commands *c)
{
	validate_redir(&c->simples[0]->in_file, &c->simples[0]->out_file);
}
/*static void	validate_command(t_commands *c)
{
	int i;
	char *infile;
	char *outfile;

	i = 0;
	if (i < c->num_of_cmds)
	{
		infile = c->simples[i]->in_file.file;
		outfile = c->simples[i]->out_file.file;
		if (access(infile, F_OK | X_OK) == 0 )
			print_error("minishell", infile, ERR_FILE, 0);
			//print_error("minishell", c->simples[i]->command, ERR_CMD, 0);
		else if (access(outfile, F_OK) == 0)
			print_error("minishell: outfile: ", ERR_FILE, NULL, 1);
	}
}*/

/*static void	validate_permission(t_commands *c)
{
	int	i;

	i = 0;
	while (i < c->num_of_cmds)
	{
		if (c->simples[i]->in_file.file != NULL)
		{
			c->simples[i]->in_file.fd = open(c->simples[i]->in_file.file, O_RDONLY);
			printf("infile[%d]: %s\n", c->simples[i]->in_file.fd, c->simples[i]->in_file.file);
			if (c->simples[i]->in_file.fd == -1)
				ft_error(WARNING, ERR_FILE, 1);
		}
		if (c->simples[i]->out_file.file != NULL)
		{
			c->simples[i]->out_file.fd = open(c->simples[i]->out_file.file,
					O_CREAT | O_WRONLY | O_TRUNC, PERMISSION);
			if (c->simples[i]->out_file.fd == -1)
				ft_error(WARNING, ERR_FILE, 1);
		}
		i++;
	}
}*/

