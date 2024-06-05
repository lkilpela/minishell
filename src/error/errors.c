/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 05:25:06 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 13:28:30 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_error(int exit_code)
{
	perror(ERR_MS);
	ms_exit(FATAL, exit_code);
}

/*int	pipe_start_end(t_token_list *tokens)
{
	if (tokens->type == OP_PIPE)
		return (0);
	while (tokens)
		tokens = tokens->next;
	if (tokens->type == OP_PIPE)
		return (0);
	return (1);
}*/