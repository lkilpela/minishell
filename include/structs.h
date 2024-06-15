/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 10:11:14 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/14 00:37:57 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/******************************************************************************\
 * MINISHELL
\******************************************************************************/
typedef struct s_var_list	t_var_list;
typedef struct s_token_list	t_token_list;
typedef struct s_cmd		t_cmd;
typedef struct s_builtin	t_builtin;

typedef struct s_ms
{
	char				**argv;
	int					argc;
	char				**envp;
	char				**paths;
	uint8_t				exit;
	t_var_list			*var_list;
	t_token_list		*tokens;
	int					max_fd;
	t_list				*commands;
	t_list				*local_var_assign;
	pid_t				*pids;
	pid_t				pid;
	int					pipefd[2];
	int					status;
	sig_atomic_t		interrupt;
	char				*executable;
	int					cmds_num;
	const t_builtin		*builtins;
	char				*pwd;
	char				*oldpwd;
}			t_ms;

/******************************************************************************\
 * BUILTINS
\******************************************************************************/
typedef struct s_builtin
{
	char	*name;
	void	(*func)(t_cmd *);
	int		special;
}			t_builtin;

/******************************************************************************\
 * FILES
\******************************************************************************/
typedef enum e_file
{
	INFILE,
	OUTFILE,
	HEREDOC
}	t_file;

typedef enum e_signal
{
	SIG_MAIN,
	SIG_FORK,
	SIG_HD
}			t_signal;

typedef struct s_redir
{
	char	*file;
	t_file	type;
	int		append;
	int		fd;
}			t_redir;

/******************************************************************************\
 * TOKENIZER
\******************************************************************************/
typedef enum e_token_type
{
	WORD,
	OP_PIPE,
	OP_LESS,
	OP_GREAT,
	OP_DLESS,
	OP_DGREAT,
}	t_token_type;

typedef struct s_token_list
{
	char				*value;
	t_token_type		type;
	int					expand;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}			t_token_list;

/******************************************************************************\
 * VARS
\******************************************************************************/
typedef struct s_var_list
{
	char				*key;
	char				*value;
	int					is_set;
	int					is_local;
	struct s_var_list	*next;
	struct s_var_list	*previous;
}			t_var_list;

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

/******************************************************************************\
 * PARSER
\******************************************************************************/
typedef struct s_cmd
{
	char	*command;
	int		num_of_args;
	t_redir	in_file;
	t_redir	out_file;
	t_list	*redirs;
	int		heredoc_expand;
	char	*heredoc_delim;
	char	**args;
	int		arg_index;
	char	*exec_path;
}			t_cmd;

/******************************************************************************\
 * ERROR
\******************************************************************************/

typedef enum e_err
{
	FATAL,
	RELINE
}			t_err;

#endif