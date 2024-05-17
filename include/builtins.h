#ifndef BUILTINS_H
# define BUILTINS_H

# include <minishell.h>
# include <parser.h>
# include <tokenizer.h>

void	built_echo(t_simple_cmd *cmd);
void	built_pwd(void);

#endif