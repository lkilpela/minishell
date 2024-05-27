/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 19:01:58 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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