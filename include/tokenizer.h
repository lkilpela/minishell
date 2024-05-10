#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>

# define DOLLAR	"$" // // denote variables ($)

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
	NEWLINE,	// end of a command
	SPACE 		// sperate different parts of a command
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
	t_token				token;	// current token
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

// a shell variable
typedef struct s_var
{
	const char	*name;	// name of variable
	char		*value;	// value of variable
}				t_var;

// list of shell variables
typedef struct s_var_list
{
	t_var				var;	//
	struct s_var_list	*next;
}				t_var_list;

#endif