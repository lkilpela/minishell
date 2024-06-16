/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/06/14 01:03:35 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	rl_history(char *input)
{
	static char	*last = NULL;

	if (*input && (!last || ft_strcmp(last, input)))
	{
		add_history(input);
		ft_free((void **)&last);
		last = ft_safe_strdup(input);
	}
}

static void	run_commands(void)
{
	ms()->commands = parser(ms()->tokens);
	ms()->paths = get_path_dirs();
	local_variables();
	execute_commands(ms()->commands);
}

void	minishell_loop(void)
{
	char			*input;
	int				all_good;

	while (42)
	{
		set_signals(SIG_MAIN);
		all_good = 1;
		if (isatty(fileno(stdin)))
			input = readline(GREEN PROMPT RESET);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			input = ft_strtrim(line, "\n");
			free(line);
		}
		if (input == NULL)
			built_exit(NULL);
		add_to_lal(input);
		rl_history(input);
		if (all_good && !quote_match_check(input))
			all_good = ms_exit(RELINE, E_CODE_SYNTX);
		if (all_good)
			ms()->tokens = new_tokenizer(input, 1);
		if (all_good && !near_token_errors(ms()->tokens))
			all_good = ms_exit(RELINE, E_CODE_SYNTX);
		if (all_good)
			run_commands();
		ft_free((void **)&input);
		ms_exit(RELINE, -1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	init_minishell(argc, argv, envp);
	minishell_loop();
}
