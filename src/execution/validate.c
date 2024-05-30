/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/30 18:11:43 by codespace        ###   ########.fr       */
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
