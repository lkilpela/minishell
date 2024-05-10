/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/10 23:06:30 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//single command
typedef struct s_redir
{
	char	*file;
	int		append;
	int		fd;
}	t_redir;


typedef struct s_simple_cmd
{
	char	*command;	// value of the command
	int		num_of_args;	// number of arguments
	t_redir	in_file;
	t_redir	out_file;
	char	**args;
}			t_simple_cmd;

// collection of commands
typedef struct s_commands
{
	t_simple_cmd	**commands;		// array of simple cmds
	int				num_of_cmds;
}				t_commands;
#endif