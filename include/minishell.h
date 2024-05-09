#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

//# define TOKEN_BUFFER 64
//# define TOKENS "|<>\"\'$"

void	tok_lstadd_back(t_token_list **lst, char *str, t_tok type);

#endif