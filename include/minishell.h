#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

//# define TOKEN_BUFFER 64
//# define TOKENS "|<>\"\'$"
typedef struct s_minishell
{
	char	**argv;
	int		argc;
	char	**envp;
}				t_minishell;

//void	tok_lstadd_back(t_token_list **lst, char *str, t_tok type);
void init_minishell(int argc, char **argv, char **envp, t_minishell *m);

#endif