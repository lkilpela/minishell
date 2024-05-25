#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h> //readline
# include <readline/history.h> //readline
# include <stdio.h> //readline
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, access, getcwd, chdir
# include <string.h> //strerror
# include <errno.h> //errno

# include <libft.h>
# include <structs.h>
# include <errors.h>

# define GREEN "\001\e[0;32m\002"
# define RESET	"\001\e[0m\002"
# define BLUE "\001\e[0;34m\002"
# define CYAN "\001\e[0;36m\002"

# define PROMPT GREEN "minishell$ " RESET
# define DOLLAR_SIGN '$'
# define UNDERSCORE '_'
# define EQUAL_SIGN '='
# define S_QUOTE '\''
# define D_QUOTE '"'

// minishell
t_ms			*ms(void);
void			init_minishell(int argc, char **argv, char **envp);

// lalloc
int				same_ptr(void *ptr, void *ptr2);
void			add_to_lal(void *ptr);
void			clear_lal();
void			free_one_lal(void *ptr);

// error
int				quote_match_check(char *input);
int				post_pipe_check(t_token_list *tokens);
int				near_token_errors(t_token_list *tokens);
void			ft_error(t_err type, char *msg, int from_ms);
t_list			**allocs(void);
void			print_errno(char *from, char *bad_arg, int from_ms);

// safe
char			*ft_safe_strjoin(const char *s1, const char *s2);
char			*ft_safe_strndup(const char *s1, size_t len);
char			*ft_safe_strdup(const char *s1);
void			*ft_safe_calloc(size_t count, size_t size);
char			*ft_safe_substr(const char *s, unsigned int start, size_t len);
void			ft_free(void **ptr);

// vars list
t_var_list 		*get_envp(char **envp);
void			add_var(char *str);
char			*lookup_var(char *var_name);
void			var_remove(char *keyval);
void			process_var_assignment(char **input);

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
char			*expand_with_condition(char *str, int last_was_dless);

// tokenizer
int				token_len(char *str);
t_token			*create_token(char *str);
void			add_token(t_token_list **lst, char *str);
t_token_list	*tokenizer(char *str);
t_token_list 	*retokenizer(t_token_list **t);

// parser

t_simple_cmd	*simple_cmd(t_token_list **tokens);
t_commands		*parser(t_token_list *tokens);
t_token_list	*get_redir(t_simple_cmd *simple, t_token_list *tokens);

//builtins
void			built_echo(t_simple_cmd *cmd);
void			built_pwd(void);
void			built_exit(void);
void			built_cd(t_simple_cmd *cmd);
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
char			*ft_strndup(const char *str, size_t len);
int				ft_strcmp(char *s1, char *s2);

// FOR TESTING **REMOVE WHEN SUBMIT**
void 			print_var_list(void);
void			print_lalloc();
void			free_var_list(void);
void 			print_last_node(void);
void 			print_tokens(t_token_list *lst);
void			free_token_list(t_token_list **lst);
void			print_commands(t_commands *cmds);
void 			print_a_token(t_token_list *lst);
void			free_arrays(char **arrays);
void 			print_last_token_node(t_token_list *t);
char			*get_type_str(int e);
void			print_commands(t_commands *cmds);
void			print_simple_cmd(t_simple_cmd *cmd);


#endif