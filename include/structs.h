/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/25 01:09:30 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/
typedef struct s_var_list t_var_list;

typedef struct s_ms
{
	char		**argv;
	int			argc;
	char		**envp;
	char		**paths;	// Array of paths for executable lookup
	char		*executable;
	t_var_list	*var_list;
}				t_ms;

/******************************************************************************\
 * FILES
\******************************************************************************/
typedef struct s_redir
{
	char	*file;
	int		append;
	int		fd;
}				t_redir;

/******************************************************************************\
 * TOKENIZER
\******************************************************************************/
typedef enum e_token_type
{
	WORD,		// a command (ls) or argument (-l)
	OP_PIPE,	// pipe output of one cmd into another (|)
	OP_LESS,	// redirect input from a file (<)
	OP_GREAT,	// redirect output to a file (>), overwriting file if exists
	OP_DLESS,	// denote heredoc (<<)
	OP_DGREAT,	// redirect output to a file (>>), appending to file if exists
	UNKNOWN
}			t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}			t_quote_type;

typedef enum e_err
{
	FATAL,
	WARNING
}			t_err;

// single token struct
typedef struct s_token
{
	char			*value;
	t_token_type	type;
}				t_token;

// a token node in linked list
typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}				t_token_list;

// variables
struct s_var_list
{
	char				*key;	// name of variable
	char				*value;	// value of variable
	struct s_var_list	*next; 
	struct s_var_list	*previous; 
};

/******************************************************************************\
 * PARSER
\******************************************************************************/
typedef struct s_simple_cmd
{
	char	*command;
	int		num_of_args;
	t_redir	in_file;
	t_redir	out_file;
	char	*heredoc;
	char	**args;
}			t_simple_cmd;

typedef struct s_commands
{
	t_simple_cmd	**simples;
	int				num_of_cmds;
}				t_commands;

#endif