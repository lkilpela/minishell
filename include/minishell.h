/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:50:28 by aklein            #+#    #+#             */
/*   Updated: 2024/06/04 04:24:56 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //readline
# include <readline/readline.h> //readline
# include <readline/history.h> //readline
# include <stdlib.h> //malloc, free
# include <unistd.h> //write, access, getcwd, chdir
# include <string.h> //strerror
# include <errno.h> //errno
# include <signal.h> //signal, sigaction
# include <sys/wait.h> //waitpid

# include <libft.h>
# include <structs.h>
# include <errors.h>

// # define GREEN "\001\e[0;32m\002"
// # define RESET	"\001\e[0m\002"
// # define BLUE "\001\e[0;34m\002"
// # define CYAN "\001\e[0;36m\002"

# define GREEN ""
# define RESET ""
# define BLUE ""
# define CYAN ""

# define PROMPT "minishell$ "
# define DOLLAR_SIGN '$'
# define UNDERSCORE '_'
# define EQUAL_SIGN '='
# define S_QUOTE '\''
# define D_QUOTE '"'
# define P_WRITE 1
# define P_READ 0

// minishell
t_ms			*ms(void);


// init
void			init_minishell(int argc, char **argv, char **envp);
void			init_redir(t_cmd *cmd);

// signals
void			init_signals();
//void			sigint_handler(int sig);

// lalloc
int				same_ptr(void *ptr, void *ptr2);
void			add_to_lal(void *ptr);
void			clear_lal();
void			free_one_lal(void *ptr);

// error
int				ms_exit(t_err type, int error_code);
int				quote_match_check(char *input);
int				pipe_start_end(t_token_list *tokens);
int				near_token_errors(t_token_list *tokens);
void			ft_error(int exit_code);
t_list			**allocs(void);
void			print_error(char *from, char *bad_arg, char *custom, int is_errno);

// safe
char			*ft_safe_strjoin(const char *s1, const char *s2);
char			*ft_safe_strndup(const char *s1, size_t len);
char			*ft_safe_strdup(const char *s1);
void			*ft_safe_calloc(size_t count, size_t size);
char			*ft_safe_substr(const char *s, unsigned int start, size_t len);
void			*ft_safe_lstnew(void *content);
char			*ft_safe_itoa(int n);
void			ft_free(void **ptr);

void			safe_dup2(int fd, int fd2);
void			safe_close(int fd);
void			safe_pipe(int *pipedes);
int				safe_fork(void);

// vars list
t_var_list 		*get_envp(char **envp);
void			extract_var(char *str, char **key, char **value);
void			add_var(char *str);
char			*lookup_var(char *var_name);
void			var_remove(char *keyval);

//env var
int				env_array_size(char **envp);
char			**env_array_dup(char **envp, int size, int cut);
void			env_free_array(char **envp);
int				env_key_len(char *env);
int				env_is_env(char *env);
int				env_exists(char *keyval);
void			env_remove(char *keyval);
void			env_add(char *keyval);

// expand

char			*exp_next_var(char *var, char **start);
char			*exp_word(char *str_start);
char			*heredoc_exp(char *str_start);
void			list_to_list(t_token_list **lst, t_token_list *add, t_token_list **index);

// tokenizer
t_token_list	*new_tokenizer(char *str);
void			exp_and_insert(t_token_list **lst);
int				token_len(char *str);
void			extract_token(char *str, char **value, t_token_type *type);
t_token_list	*create_token(t_token_type type, char *value);
t_quote_type	update_quote_type(t_quote_type quote_type, char c);

// parser
t_cmd			*simple_cmd(t_token_list **tokens);
t_list			*parser(t_token_list *tokens);
t_token_list	*get_redir(t_cmd *cmd, t_token_list *tokens);
char			*handle_node_quotes(char *val);
int				has_quotes(char *value);
int				is_ambiguous(char *val, t_token_list *tokens);

// execution
void			init_path_dirs(void);
void			execute_commands(t_list *c);
void			parent(t_list *cmds, int *pipe_in);
void			child(t_list *cmds, int *pipe_in);
int 			validate_redir(t_redir *file);
int				builtin_cmd(t_cmd *cmd);
void			validate_command(t_cmd *cmd);
char			*find_executable(t_cmd *cmd);

//builtins
void			built_echo(t_cmd *cmds);
void			built_pwd(void);
void			built_exit(t_cmd *cmds);
void			built_cd(t_cmd *cmds);
void			built_env(int declare);
void			built_export(t_cmd *cmds);
void			built_unset(t_cmd *cmds);

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
void 			print_last_node(void);
void 			print_tokens(t_token_list *lst);
void			free_token_list(t_token_list **lst);
void 			print_a_token(t_token_list *lst);
void 			print_last_token_node(t_token_list *t);
char			*get_type_str(int e);
void			print_cmds(t_list *cmd);
void			print_executable(t_list *cmds);

#endif