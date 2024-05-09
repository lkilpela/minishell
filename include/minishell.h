#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

//# define TOKEN_BUFFER 64
//# define TOKENS "|<>\"\'$"


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
	DOLLAR, 	// denote variables ($)
	NEWLINE,	//end of a command
	SPACE 		//sperate different parts of a command
}			t_token_type;

// single token struct
typedef struct s_token
{
	char		*value; // token string
	t_token_type type;	// token type
}				t_token;


// token list struct
typedef struct s_token_list
{
	t_token				token;	// current token
	struct s_tok_list	*next;	// pointer to next token
}				t_token_list;


typedef struct s_tokenizer
{
	char			*input; 		// input string to be tokenized
	int				pos;			// current position in input string
	t_token			current_token; // current token being processed
	t_token_list	*tokens; 		// list of all tokens parsed from the input
}				t_tokenizer;

void	tok_lstadd_back(t_tok_list **lst, char *str, t_tok type);

#endif