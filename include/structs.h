/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/23 14:40:24 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/

typedef struct s_ms
{
	char		**argv;
	int			argc;
	char		**envp;
	char		**paths;	// Array of paths for executable lookup
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
	VAR,		// $HOME is treated as a single VAR token´
	UNKNOWN
}			t_token_type;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}			t_quote_type;

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
typedef struct s_var_list
{
	char				*key;
	char				*value;
	struct s_var_list	*next;
}				t_var_list;

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