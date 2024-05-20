#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> //readline
# include <readline/history.h> //readline
# include <stdio.h> //readline
# include <stdlib.h> //malloc, free
# include <unistd.h> //write 

# include <libft.h>
# include <structs.h>

# define GREEN "\e[0;32m"
# define RESET	"\e[0m"
# define BLUE "\e[0;34m"
# define CYAN "\e[0;36m"

# define PROMPT GREEN "minishell$ " RESET
# define DOLLAR_SIGN '$'
# define UNDERSCORE '_'
# define EQUAL_SIGN '='
# define S_QUOTE '\''
# define D_QUOTE '"' 

// minishell
t_ms			*ms(void);
void			init_minishell(int argc, char **argv, char **envp);

// environment var
t_var_list 		*get_envp(char **envp);
void			add_var(t_var_list **lst, char *str);
char			*lookup_var(char *var_name, t_var_list *v);

// quote handler
char 			*handle_quotes(char *str, t_var_list *v);

// tokenizer
t_token_list	*tokenizer(char *str, t_var_list *v);
void 			retokenizer(char *str, t_var_list *v, t_token_list **lst);

// expander
char 			*expand_variable(char *str, t_var_list *v);
void			process_var_assignment(char **input, t_var_list *v);

// parser
t_commands		*parser(t_token_list *tokens);

//builtins
void			built_echo(t_simple_cmd *cmd);
void			built_pwd(t_var_list *v);

// utils
int				is_word(char c);
int				is_whitespace(char c);
int				is_quote(char c);
int				is_operator(char c);
int				is_double_operator(char *str);
char			*skip_whitespaces(char *str);
char			*skip_word(char *str);
char			*skip_op(char *str);
char			*skip_quote(char *str);
char			*skip_variable(char *str);

// utils2
int				get_token_len(char *str);
char			*ft_strndup(char *str, size_t len);
int				ft_strcmp(char *s1, char *s2);

// FOR TESTING **REMOVE WHEN SUBMIT**
void 			print_var_list(t_var_list *v);
void			free_var_list(t_var_list *list);
void 			print_last_node(t_var_list *v);
void 			print_tokens(t_token_list *lst);
void			free_token_list(t_token_list **lst);
void			print_commands(t_commands *cmds);
void 			print_a_token(t_token_list *lst);
void			free_arrays(char **arrays);

#endif              