/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 04:22:30 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/12 09:19:37 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	main_sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	fork_signal_handler(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', 1);
	if (sig == SIGQUIT)
		ft_putstr_fd(ERR_FORK_QUIT, 1);
}

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		ms_exit(FATAL, EXIT_SUCCESS);
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals(t_signal mode)
{
	if (mode == SIG_MAIN)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, main_sigint_handler);
	}
	if (mode == SIG_HD)
	{
		signal(SIGQUIT, heredoc_signal_handler);
		signal(SIGINT, heredoc_signal_handler);
	}
	if (mode == SIG_FORK)
	{
		signal(SIGQUIT, fork_signal_handler);
		signal(SIGINT, fork_signal_handler);
	}
}
