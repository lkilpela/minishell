/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/09 12:11:21 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//single command
typedef struct s_simple_cmd
{
	char	*command;	// value of the command
	int		num_of_args;	// number of arguments
	char	**args;
}			t_simple_cmd;

// collection of commands
typedef struct s_commands
{
	t_simple_cmd	**commands;		// array of simple cmds
	char			*in_file;
	char			*out_file;
}				t_commands;
#endif