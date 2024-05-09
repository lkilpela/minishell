#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

# define TOKEN_BUFFER 64
# define TOKENS "|<>\"\'$"


typedef enum e_tok
{
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	DOLLAR = '$',
	WORD = 4242
}	t_tok;

typedef struct s_tok_list
{
	char				*str;
	t_tok				type;	
	struct s_tok_list	*next;
}	t_tok_list;
#endif