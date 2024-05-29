/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 23:05:48 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

# define PERMISSION 0644

void validate_redir(t_redir *infile, t_redir *outfile)
{
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
