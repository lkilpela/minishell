#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>

# define GREEN "\e[0;32m"
# define RESET	"\e[0m"

typedef struct s_minishell
{
	char	**argv;
	int		argc;
	char	**envp;
	char	**paths;	// Array of paths for executable lookup
}				t_minishell;

void init_minishell(int argc, char **argv, char **envp, t_minishell *m);

#endif