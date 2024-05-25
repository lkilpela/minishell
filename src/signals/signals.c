#include <minishell.h>

void	sigint_handler(int sig)
{
    if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals()
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}