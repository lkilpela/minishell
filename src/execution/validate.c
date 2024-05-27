/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/27 15:44:50 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	validate_command(t_commands *c)
{
	int i;
	char *infile;
	char *outfile;

	i = 0;
	infile = c->simples[i]->in_file.file;
	outfile = c->simples[i]->out_file.append;
	if (i < c->num_of_cmds)
	{
		if (ft_strlen(infile) == 0 || ft_strlen(outfile) == 0 )
			print_error("minishell: ", infile, NULL, 1);
	}
}