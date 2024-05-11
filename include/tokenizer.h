#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include <stdio.h>

# define DOLLAR_CHAR '$' // // denote variables ($)
# define SPACE_CHAR ' '
# define PIPE_CHAR "|"
# define LESS_CHAR "<"
# define GREAT_CHAR '>'

typedef enum e_token_type
{
	WORD,		// a command (ls) or argument (-l)
	PIPE,		// pipe output of one cmd into another (|)
	LESS,		// redirect input from a file (<)
	GREAT,		// redirect output to a file (>), overwriting file if exists
	D_LESS,		// denote heredoc (<<)
	D_GREAT,	// redirect output to a file (>>), appending to file if exists
	S_QUOTE,	// start or end of a single-quoted string (')
	D_QUOTE,	// start or end of a double-quoted string (")
	VAR, 		// $HOME is treated as a single VAR token
	T_NEWLINE,
	T_SPACE	// sperate different parts of a command
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

// state of the tokenizer while it's processing an input string
typedef struct s_tokenizer
{
	char			*input; 		// input string to be tokenized
	int				pos;			// current position in input string
	t_token			current_token; // current token being processed
	t_token_list	*tokens; 		// list of all tokens parsed from the input
}				t_tokenizer;

// single variable
typedef struct s_var
{
	const char	*name;	// name of variable
	char		*value;	// value of variable
}				t_var;

// variables
typedef struct s_var_array
{
	t_var	*vars; // a pointer to an array of t_var
	int		size; // number of variable in the array
}				t_var_array;


void init_tokenizer(t_tokenizer *t, char *input);

// token list
void	add_node(t_token_list **lst, t_token *token);
void	clear_list(t_token_list **lst);
void	print_tokens(t_token_list *lst);
void	delone_node(t_token_list *lst);
void	free_list(t_token_list **lst);

// tokenizer
void tokenizer();

// utils
char	*skip_whitespaces(char *str);
char	*skip_word(char *str);

#endif