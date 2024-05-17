/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/17 18:02:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <parser.h>

void	process_input(char *input, t_var_list **lst)
{
	char	*equal_pos;
	char	*temp;

	equal_pos = ft_strchr(input, '=');
	if (equal_pos)
		add_var(&lst, input);
	else
	{
		temp = expand_variable(input, lst);
		printf("expanded_str: %s\n", temp);
		free(temp);
	}
}

void minishell_loop()
{
	char			*input;
	t_token_list	*lst;
	//t_tokenizer	t;

	while (42)
	{
		input = readline(PROMPT);
		if (!input)
			break;
		add_history(input);
		//init_tokenizer(&t, input);
		lst = tokenizer(input);
		print_tokens(lst);
		print_commands(parser(lst));
		free_list(&lst);
		process_input(input, lst);
		free(input);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	//t_var_list *lst;

	init_minishell(argc, argv, envp, &m);
	//lst = get_envp(envp);
	//print_envp(lst);
	//free_var_list(lst);
	minishell_loop();
}
