#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <libft.h>
# include <unistd.h>

# define GREEN "\e[0;32m"
# define RESET	"\e[0m"

# define PROMPT GREEN "minishell$ " RESET

typedef struct s_ms
{
	char	**argv;
	int		argc;
	char	**envp;
	char	**paths;	// Array of paths for executable lookup
}				t_ms;

t_ms		*ms(void);
void		init_minishell(int argc, char **argv, char **envp);

#endif