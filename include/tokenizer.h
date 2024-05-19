#ifndef TOKENIZER_H
# define TOKENIZER_H

# define BLUE "\e[0;34m"
# define CYAN "\e[0;36m"
# define RESET	"\e[0m"

# define DOLLAR '$' // denote variables ($)
# define UNDERSCORE '_' 

typedef enum e_token_type
{
	WORD,		// a command (ls) or argument (-l)
	OP_PIPE,		// pipe output of one cmd into another (|)
	OP_LESS,		// redirect input from a file (<)
	OP_GREAT,		// redirect output to a file (>), overwriting file if exists
	OP_DLESS,		// denote heredoc (<<)
	OP_DGREAT,	// redirect output to a file (>>), appending to file if exists
	//S_QUOTE,	// start or end of a single-quoted string (')
	//D_QUOTE,	// start or end of a double-quoted string (")
	VAR, 		// $HOME is treated as a single VAR token
	//T_NEWLINE,
	//T_SPACE,	// sperate different parts of a command
	//COMPLEX_WORD,
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

#endif