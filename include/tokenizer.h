#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdlib.h>
# include <stdio.h>
# include <libft.h>

# define BLUE "\e[0;34m"
# define CYAN "\e[0;36m"
# define RESET	"\e[0m"

# define DOLLAR '$' // denote variables ($)
# define UNDERSCORE '_' 

typedef enum e_token_type
{
	WORD,		// a command (ls) or argument (-l)
	OP_PIPE,		// pipe output of one cmd into another (|)
	OP_LESS,		// redirect input from a file (<)
	OP_GREAT,		// redirect output to a file (>), overwriting file if exists
	OP_DLESS,		// denote heredoc (<<)
	OP_DGREAT,	// redirect output to a file (>>), appending to file if exists
	//S_QUOTE,	// start or end of a single-quoted string (')
	//D_QUOTE,	// start or end of a double-quoted string (")
	VAR, 		// $HOME is treated as a single VAR token
	//T_NEWLINE,
	//T_SPACE,	// sperate different parts of a command
	//COMPLEX_WORD,
	UNKNOWN
}			t_token_type;

// single token struct
typedef struct s_token
{
	char		*value; // token string
	t_token_type type;	// token type
}				t_token;

// a token node in linked list
typedef struct s_token_list
{
	t_token				*token;	// current token
	struct s_token_list	*next;	// pointer to next token
}				t_token_list;

// state of the tokenizer while it's processing an input string
typedef struct s_tokenizer
{
	char			*input; 		// input string to be tokenized
	int				pos;			// current position in input string
	t_token			current_token; // current token being processed
	t_token_list	*tokens; 		// list of all tokens parsed from the input
}				t_tokenizer;

// single env variable
typedef struct s_var
{
	char	*name;	// name of variable
	char	*value;	// value of variable
}				t_var;

// variables
typedef struct s_var_list
{
	t_var				*current_var; 
	struct s_var_list	*next; 
}				t_var_list;

// init
//void			init_tokenizer(t_tokenizer *t, char *input);

// environment var
void			free_var_list(t_var_list *list);
t_var_list 		*get_envp(char **envp);
void 			print_var_list(t_var_list *v);
char 			*remove_quotes(char *str);
void			add_var(t_var_list **lst, char *str);


// token list
//void			append_node(t_token_list **lst, t_token token);
//void			free_list(t_token_list **lst);
//void			print_tokens(t_token_list *lst);

// tokenizer
//t_token_list	*tokenize_input(char *str);
//t_token			create_token(char *str);

//optimize
t_token_list	*tokenizer(char *str, t_var_list *v);
void 			print_tokens(t_token_list *lst);
void			free_token_list(t_token_list **lst);

//expander
char 			*expand_variable(char *str, t_var_list *v);
void			process_var_assigment(char **input, t_var_list *v);

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


#endif