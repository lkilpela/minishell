/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:09:37 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/05 13:45:09 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_content(void *content)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
}

static void	clear_lal(void)
{
	t_list	**lalloc;

	lalloc = allocs();
	ft_lstclear(lalloc, free_content);
}

static void	clear_tokens(void)
{
	t_token_list	*tokens;
	t_token_list	*next_token;

	tokens = ms()->tokens;
	while (tokens)
	{
		next_token = tokens->next;
		ft_free((void **)&tokens->value);
		ft_free((void **)&tokens);
		tokens = next_token;
	}
	ms()->tokens = NULL;
}

static void	clear_cmds(void)
{
	t_list	*cmds;
	t_cmd	*cmd;
	int		i;

	cmds = ms()->commands;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		ft_free((void **)&cmd->command);
		ft_free((void **)&cmd->heredoc);
		ft_free((void **)&cmd->heredoc_delim);
		ft_free((void **)&cmd->exec_path);
		i = 0;
		while (cmd->args[i])
			ft_free((void **)&cmd->args[i++]);
		ft_free((void **)&cmd->args);
		cmds = cmds->next;
	}
	ms()->commands = NULL;
}

int	ms_exit(t_err type, int error_code)
{
	if (error_code != -1)
		ms()->exit = error_code;
	if (type == RELINE)
	{
		clear_cmds();
		clear_tokens();
		return (0);
	}
	if (type == FATAL)
	{
		clear_lal();
		exit(ms()->exit);
	}
	return (1);
}
