#include <minishell.h>

void	sigint_handler(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	write(1, "\n", 1);
	write(1, PROMPT, ft_strlen(PROMPT));
}

void	init_signals()
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &sigint_handler;
	sigaction(SIGINT, &act, NULL);
	signal(SIGQUIT, SIG_IGN);
}