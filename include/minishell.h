#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

# define TOKEN_BUFFER 64
# define TOKENS "|<>\"\'$"

typedef struct s_token t_token;


typedef enum e_tok
{
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	S_QUOTE = '\'',
	D_QUOTE = '\"',
	DOLLAR = '$',
	WORD
}	t_tok;

struct s_token
{
	char	*str;
	t_tok	type;
};

#endif