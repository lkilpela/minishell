/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:58:22 by aklein            #+#    #+#             */
/*   Updated: 2024/05/15 20:53:00 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <tokenizer.h>
#include <parser.h>

/*void minishell_loop()
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
		lst = tokenize_input(input);
		print_tokens(lst);
		print_commands(parser(lst));
		free_list(&lst);
		free(input);
	}
}*/

int main(int argc, char **argv, char **envp)
{
	t_minishell	m;
	//t_var_list *lst;

	init_minishell(argc, argv, envp, &m);
	//lst = get_envp(envp);
	// Initialize a t_var_list with some variables
    t_var_list v;
    v.current_var = malloc(sizeof(t_var));
    v.current_var->name = "NAME";
    v.current_var->value = "value";

    // Test expand_variable with some strings
    char *str1 = "echo $NAME";
    char *str2 = "test$NAME";
    char *str3 = "$NAME";

    char *expanded_str1 = expand_variable(str1, &v);
    char *expanded_str2 = expand_variable(str2, &v);
    char *expanded_str3 = expand_variable(str3, &v);

    printf("%s\n", expanded_str1);  // Should print: echo value
    printf("%s\n", expanded_str2);  // Should print: testvalue
    printf("%s\n", expanded_str3);  // Should print: value

    // Free the expanded strings
    free(expanded_str1);
    free(expanded_str2);
    free(expanded_str3);

    // Free the variable list
    free(v.current_var);
	//print_envp(lst);
	//free_var_list(lst);
	//minishell_loop();
}
