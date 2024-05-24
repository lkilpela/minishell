#include <minishell.h>

void	error_print(int err)
{
	printf("%s\n", strerror(err));
}

void	ft_error(char *msg, int check_errno)
{
	if (check_errno)
		error_print(errno);
	printf("%s\n", msg);
}