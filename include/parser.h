/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/09 10:27:23 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//single command
typedef struct s_simple_cmd
{
	char	*value;	// value of the command
}				t_simple_cmd;

// collection of commands
typedef struct s_commands
{
	t_simple_cmd	**args; 		// array of arguments
	int				num_of_args;	// number of arguments
	
}				t_commands;
#endif