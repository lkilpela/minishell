/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:51 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/29 10:18:58 by lkilpela         ###   ########.fr       */
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

void	validate_permission(t_simple_cmd *s)
{
	s->in_file.fd = open(s->in_file.file, O_RDONLY);
	if (s->in_file.fd == -1)
		ft_error(WARNING, ERR_PERM, 1);
	s->out_file.fd = open(s->out_file.file,
			O_CREAT | O_WRONLY | O_TRUNC, PERMISSION);
	if (s->out_file.fd == -1)
		ft_error(WARNING, ERR_PERM, 1);
	
}
