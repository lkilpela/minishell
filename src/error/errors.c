#include <minishell.h>

void	print_error(int err)
{
	printf("%s\n", strerror(err));
}

void	ft_error(t_err type, char *msg, int check_errno)
{
	if (check_errno)
		print_error(errno);
	if (msg)
		printf("%s\n", msg);
	if (type == FATAL)
		exit(EXIT_FAILURE);
}