#include <minishell.h>

void	ft_error(t_err type, char *msg, int from_ms)
{
	if (from_ms)
	{
		ft_putstr_fd(ms()->executable, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	if (type == FATAL)
	{
		clear_lal();
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}

void	print_error(char *from, char *bad_arg, char *custom, int is_errno)
{
	if (from)
	{
		ft_putstr_fd(from, 2);
		ft_putstr_fd(": ", 2);
	}
	if (is_errno)
		if (bad_arg)
			perror(bad_arg);
		else
			perror(NULL);
	else
	{
		if (bad_arg)
		{
			ft_putstr_fd(bad_arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(custom, 2);
	}
}

int	quote_match_check(char *input)
{
	char	quote_type;

	quote_type = 0;
	while (*input)
	{
		if (!quote_type && is_quote(*input))
			quote_type = *input;
		else if (*input == quote_type)
			quote_type = 0;
		input++;
	}
	return (quote_type == 0);
}

int	post_pipe_check(t_token_list *tokens)
{
	while (tokens)
	{
		if (tokens->token->type == OP_PIPE)
		{
			if (tokens->next == NULL)
			{
				ft_error(WARNING, ERR_PIPES, 1);
				return (0);
			}
		}
		tokens = tokens->next;
	}
	return (1);
}

char	*get_near_error(t_token_list *near)
{
	char	*token_val;
	char	*start;
	char	*final;

	if (!near)
		token_val = NL;
	else
		token_val = near->token->value;
	start = ft_safe_strjoin(ERR_NEAR_TOKEN, token_val);
	final = ft_safe_strjoin(start, "\'");
	ft_free((void **)&start);
	return (final);
}

int	check_op_syntax(t_token_list *token)
{
	t_token_type	current;

	current = token->token->type;
	if (!token->next)
		return (0);
	if (current == OP_PIPE)
		if (token->next->token->type == OP_PIPE)
			return (0);
	if (current >= OP_LESS && current <= OP_DGREAT)
		if (token->next->token->type != WORD)
			return (0);
	return (1);
}

int	near_token_errors(t_token_list *tokens)
{
	t_token_list	*near;
	char			*err_msg;

	while (tokens)
	{
		near = tokens->next;
		if (tokens->token->type != WORD)
			if (!check_op_syntax(tokens))
			{
				err_msg = get_near_error(near);
				ft_error(WARNING, err_msg, 1);
				ft_free((void **)&err_msg);
				return (0);
			}
		tokens = tokens->next;
	}
	return (1);
}
