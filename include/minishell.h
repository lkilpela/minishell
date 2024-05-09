#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

//# define TOKEN_BUFFER 64
//# define TOKENS "|<>\"\'$"


typedef enum e_tok_type
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
}			t_tok_type;

typedef struct s_tok_list
{
	char				*str;
	t_tok_type			type;
	struct s_tok_list	*next;
}	t_tok_list;

void	tok_lstadd_back(t_tok_list **lst, char *str, t_tok type);

#endif