/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/31 01:31:55 by aklein           ###   ########.fr       */
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
			print_error("minishell", infile->file, NULL, 1);
			exit(EXIT_FAILURE);
		}
	}
	else
		infile->fd = -1;
	if (outfile->file)
	{
		outfile->fd = open(outfile->file,
				O_CREAT | O_WRONLY | O_TRUNC, PERMISSION);
		if (outfile->fd == -1)
		{
			print_error("minishell", outfile->file, NULL, 1);
			exit(EXIT_FAILURE);
		}
	}
	else
		outfile->fd = -1;
}

void	validate_arguments(t_list *cmds)
{
	t_cmd			*first_cmd;
	t_redir			in;
	t_redir			out;
	
	first_cmd = (t_cmd *)cmds->content;
	in = first_cmd->in_file;
	out = first_cmd->out_file;
	validate_redir(&in, &out);
}
