/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/20 09:38:47 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/

typedef struct s_ms
{
	char	**argv;
	int		argc;
	char	**envp;
	char	**paths;	// Array of paths for executable lookup
}				t_ms;

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
 * TOKENIZER
\******************************************************************************/
typedef enum e_token_type
{
	WORD,		// a command (ls) or argument (-l)
	OP_PIPE,		// pipe output of one cmd into another (|)
	OP_LESS,		// redirect input from a file (<)
	OP_GREAT,		// redirect output to a file (>), overwriting file if exists
	OP_DLESS,		// denote heredoc (<<)
	OP_DGREAT,	// redirect output to a file (>>), appending to file if exists
	VAR, 		// $HOME is treated as a single VAR token´
	UNKNOWN
}			t_token_type;

// single token struct
typedef struct s_token
{
	char		*value; // token string
	t_token_type type;	// token type
}				t_token;

// a token node in linked list
typedef struct s_token_list
{
	t_token				*token;	// current token
	struct s_token_list	*next;	// pointer to next token
}				t_token_list;

// single env variable
typedef struct s_var
{
	char	*name;	// name of variable
	char	*value;	// value of variable
}				t_var;

// variables
typedef struct s_var_list
{
	t_var				*current_var; 
	struct s_var_list	*next; 
}				t_var_list;

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