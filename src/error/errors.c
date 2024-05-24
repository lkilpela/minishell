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