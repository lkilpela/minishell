/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 13:02:44 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/
typedef struct s_ms
{
	char				**argv;
	int					argc;
	char				**envp;
	char				**paths;
	uint8_t				exit;
	t_var_list			*var_list;
	t_token_list		*tokens;
	t_list				*commands;
	pid_t				*pids;
	pid_t				pid;
	int					pipefd[2];
	int					status;
	char				*executable;
	int					cmds_num;
	const t_builtin		*builtins;
}					t_ms;

/******************************************************************************\
 * BUILTINS
\******************************************************************************/
typedef struct s_builtin
{
	char	*name;
	void	(*func)(t_cmd *);
	int		special;
}				t_builtin;

/******************************************************************************\
 * FILES
\******************************************************************************/
typedef enum e_file
{
	INFILE,
	OUTFILE
}			t_file;

typedef struct s_redir
{
	char	*file;
	t_file	type;
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

// a token node in linked list
typedef struct s_token_list
{
	char				*value;
	t_token_type		type;
	int					expand;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}				t_token_list;

/******************************************************************************\
 * VARS
\******************************************************************************/
typedef struct s_var_list
{
	char				*key;
	char				*value;
	struct s_var_list	*next;
	struct s_var_list	*previous;
}				t_var_list;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}			t_quote_type;

/******************************************************************************\
 * PARSER
\******************************************************************************/
typedef struct s_cmd
{
	char	*command;
	int		num_of_args;
	t_redir	in_file;
	t_redir	out_file;
	char	*heredoc;
	int		heredoc_expand;
	char	*heredoc_delim;
	char	**args;
	char	*exec_path;
}			t_cmd;

/******************************************************************************\
 * ERROR
\******************************************************************************/

typedef enum e_err
{
	FATAL,
	WARNING,
	RELINE
}			t_err;

#endif