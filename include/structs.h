/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/19 14:02:04 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/

typedef struct s_minishell
{
	char	**argv;
	int		argc;
	char	**envp;
	char	**paths;	// Array of paths for executable lookup
}				t_minishell;

/******************************************************************************\
 * FILES
\******************************************************************************/
typedef struct s_redir
{
	char	*file;
	int		append;
	int		fd;
}	t_redir;

/******************************************************************************\
 * PARSER
\******************************************************************************/
typedef struct s_simple_cmd
{
	char	*command;	// value of the command
	int		num_of_args;	// number of arguments
	t_redir	in_file;
	t_redir	out_file;
	char 	*heredoc;
	char	**args;
}			t_simple_cmd;

typedef struct s_commands
{
	t_simple_cmd	**simples;		// array of simple cmds
	int				num_of_cmds;
}				t_commands;

#endif