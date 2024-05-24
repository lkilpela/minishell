/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:03:00 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/24 12:04:13 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_args(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->token->type != OP_PIPE)
	{
		if (tokens->token->type >= OP_LESS && tokens->token->type <= OP_DGREAT)
		{
			tokens = tokens->next;
			if (tokens->token->type == WORD)
				tokens = tokens->next;
			continue ;
		}
		if (tokens->token->type == WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

int	count_cmd(t_token_list *tokens)
{
	int	count;

	count = 1;
	while (tokens)
	{
		if (tokens->token->type == OP_PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

