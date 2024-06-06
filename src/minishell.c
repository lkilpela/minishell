/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/06/06 15:41:17 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	rl_history(char *input)
{
	static char	*last = NULL;

	if (!last || ft_strcmp(last, input) != 0)
		add_history(input);
	ft_free((void **)&last);
	last = ft_safe_strdup(input);
	write_history(NULL); //temp
}

void	minishell_loop(void)
{
	char			*input;
	int				all_good;

	while (42)
	{
		all_good = 1;
		input = readline(PROMPT);
		if (input == NULL)
			built_exit(NULL);
		rl_history(input);
		if (all_good && !quote_match_check(input)) // ensure quotes are balanced
			all_good = ms_exit(RELINE, E_CODE_SYNTX);
		if (all_good)
			ms()->tokens = new_tokenizer(input);
		//print_tokens(ms()->tokens);
		if (all_good && !near_token_errors(ms()->tokens)) // check for errors in token list
			all_good = ms_exit(RELINE, E_CODE_SYNTX);
		if (all_good)
		{
			ms()->commands = parser(ms()->tokens);
			init_path_dirs();
			//print_cmds(ms()->commands);
			//print_executable(ms()->commands);
			// builtin_cmd(ms()->commands); //temp
			execute_commands(ms()->commands);
		}
		ft_free((void **)&input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	init_minishell(argc, argv, envp);
	read_history(NULL);
	minishell_loop();
}
