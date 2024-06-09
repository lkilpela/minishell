/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/06/09 04:58:07 by aklein           ###   ########.fr       */
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

void	local_variables(void)
{
	t_list	*locals;
	t_list	*tmp;
	t_cmd	*cmd;
	
	locals = ms()->local_var_assign;
	while (locals)
	{
		cmd = (t_cmd *)locals->content;
		if (cmd->num_of_args > 1)
			return ;
		if (ms()->cmds_num == 0)
			add_var(cmd->args[0], 1);
		tmp = locals->next;
		ft_free((void **)&locals);
		locals = tmp;
	}
	ms()->local_var_assign = NULL;
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
			ms_exit(FATAL, ms()->exit);
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
			// t_list *cmds;
			// cmds = ms()->commands;
			// print_cmds(cmds);
			//print_executable(cmds);
			local_variables();
			execute_commands(ms()->commands);
		}
		ms_exit(RELINE, EXIT_SUCCESS); //maybe -1 for not touching the ms().exit code
	}
}

int	main(int argc, char **argv, char **envp)
{
	init_minishell(argc, argv, envp);
	read_history(NULL);
	minishell_loop();
}
