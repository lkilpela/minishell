/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:50:28 by aklein            #+#    #+#             */
/*   Updated: 2024/06/14 02:23:46 by aklein           ###   ########.fr       */
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

# define GREEN "\001\e[0;32m\002"
# define RESET	"\001\e[0m\002"
# define BLUE "\001\e[0;34m\002"
# define CYAN "\001\e[0;36m\002"

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
t_cmd			*init_cmd(t_token_list *tokens);
void			init_builtins(void);

// signals
void			set_signals(t_signal mode);

// lalloc
void			add_to_lal(void *ptr);
void			ft_free(void **ptr);
void			free_content(void *content);

// error
int				ms_exit(t_err type, int error_code);
int				quote_match_check(char *input);
int				near_token_errors(t_token_list *tokens);
void			ft_error(int exit_code);
t_list			**allocs(void);
void			print_error(char *from, char *bad_arg,
					char *custom, int is_errno);
void			clear_paths(void);

// safe
char			*ft_safe_strjoin(const char *s1, const char *s2);
char			*ft_safe_strndup(const char *s1, size_t len);
char			*ft_safe_strdup(const char *s1);
void			*ft_safe_calloc(size_t count, size_t size);
void			*ft_safe_lstnew(void *content);
char			*ft_safe_itoa(int n);
char			**ft_safe_split(const char *s, char c);
int				safe_dup(int fd);
void			safe_dup2(int fd, int fd2);
int				safe_open(char *file, int oflags, int mode);
void			safe_close(int fd);
void			safe_pipe(int *pipedes);
int				safe_fork(void);

// vars
t_var_list		*get_envp(char **envp);
void			extract_var(char *str, char **key, char **value, int *is_set);
void			add_var(char *str, int is_local);
void			add_var_to_list(t_var_list **head, t_var_list *node);
t_var_list		*create_var_node(char *key, char *value, int set, int local);
void			merge_sort(t_var_list **vars);
int				var_declared(char *key);
char			*lookup_var(char *key);
void			local_variables(void);
int				local_var(t_cmd *cmd, char *str);
void			shlvl(void);

// expander
char			*exp_word(char *str_start);
char			*exp_next_var(char *var, char **start);
void			expand_current_el(t_token_list **tokens, t_token_list **index);
int				special_local_var(t_cmd *cmd, t_token_list **tokens);
void			special_export(t_cmd *cmd, t_token_list **tokens);

// tokenizer
int				token_len(char *str);
void			extract_token(char *str, char **value, t_token_type *type);
t_token_list	*new_tokenizer(char *str, int ops);
void			list_to_list(t_token_list **lst,
					t_token_list *add, t_token_list **index);

// parser
t_cmd			*simple_cmd(t_token_list **tokens);
t_list			*parser(t_token_list *tokens);
void			get_all_redir(t_token_list *tokens, t_cmd *cmd);
void			add_redir(t_redir *redir, t_cmd	*cmd);
t_token_list	*handle_heredoc(t_cmd *cmd, t_token_list *tokens);
char			*handle_node_quotes(char *val);
void			clear_token_quotes(t_token_list *tokens);
int				has_quotes(char *value);
int				is_ambiguous(char *val, t_token_list *tokens);

// execution
char			**get_path_dirs(void);
char			*find_executable(t_cmd *cmd);
char			**build_envp(void);
void			execute_commands(t_list *c);
void			child(t_list *cmds, int *pipe_in);
int				validate_redir_list(t_cmd *cmd);
char			*heredoc(t_cmd *cmd);
void			validate_command(t_cmd *cmd);
void			close_fds(void);

//builtins
int				execute_builtin(t_cmd *cmd);
int				is_special_builtin(t_cmd *cmd);
t_builtin		get_builtin(t_cmd *cmd);
void			built_echo(t_cmd *cmds);
void			built_pwd(t_cmd *cmds);
void			built_exit(t_cmd *cmds);
void			built_cd(t_cmd *cmds);
void			built_env(t_cmd *cmds);
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
int				str_is_number(char *str);

// utils2
char			*ft_strndup(const char *str, size_t len);
int				ft_strcmp(char *s1, char *s2);

#endif