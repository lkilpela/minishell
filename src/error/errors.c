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

void	print_errno(char *from, char *bad_arg, int from_ms)
{
	if (from_ms)
	{
		ft_putstr_fd(ms()->executable, 2);
		ft_putstr_fd(": ", 2);
	}
	if (from)
	{
		ft_putstr_fd(from, 2);
		ft_putstr_fd(": ", 2);
	}
	perror(bad_arg);
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
