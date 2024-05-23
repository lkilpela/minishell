#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> //readline
# include <readline/history.h> //readline
# include <stdio.h> //readline
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, access, getcwd, chdir

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

// local var
t_var_list 		*get_envp(char **envp);
void			add_var(char *str);
char			*lookup_var(char *var_name);

//env var
int				env_array_size(char **envp);
char			**env_array_dup(char **envp, int size, int cut);
void			env_free_array(char **envp);
int				env_key_len(char *env);
int				env_is_env(char *env);
int				env_exists(char *keyval);
void			env_remove(char *keyval);
void			env_add(char *keyval);

// expander
char			*check_quotes_and_expand(char *str);

// tokenizer & var_assignment handler
int				token_len(char *str);
t_token			*create_token(char *str);
void			add_token(t_token_list **lst, char *str);
t_token_list	*tokenizer(char *str);
t_token_list 	*retokenizer(t_token_list **t);
void			process_var_assignment(char **input);

// parser
t_commands		*parser(t_token_list *tokens);

//builtins
void			built_echo(t_simple_cmd *cmd);
void			built_pwd(void);
void			built_exit(void);
void			built_cd(int argc, char **argv);
void			built_env(int declare);
void			built_export(t_simple_cmd *cmd);
void			built_unset(t_simple_cmd *cmd);

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
void 			print_var_list(void);
void			free_var_list(void);
void 			print_last_node(void);
void 			print_tokens(t_token_list *lst);
void			free_token_list(t_token_list **lst);
void			print_commands(t_commands *cmds);
void 			print_a_token(t_token_list *lst);
void			free_arrays(char **arrays);
void 			print_last_token_node(t_token_list *t);
char			*get_type_str(int e);


#endif              