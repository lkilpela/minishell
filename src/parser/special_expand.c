/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 07:23:21 by aklein            #+#    #+#             */
/*   Updated: 2024/06/10 07:27:44 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_quoted(char *str)
{
	if (*str != '"')
		return (0);
	if (str[ft_strlen(str)] != '"')
		return (0);
	return (1);
}

static char	*add_quotes(char *str)
{
	char	*tmp;
	char	*final;

	if (!is_quoted(str))
	{
		tmp = ft_safe_strjoin("\"", str);
		final = ft_safe_strjoin(tmp, "\"");
		ft_free((void **)&tmp);
	}
	return (final);
}

void	special_export(t_cmd *cmd, t_token_list **tokens)
{
	t_token_list	*next_word;
	char			*tmp;

	next_word = (*tokens)->next;
	if (ft_strcmp(cmd->command, "export") == 0)
	{
		if (next_word && next_word->type == WORD)
		{
			tmp = add_quotes(next_word->value);
			ft_free((void **)&next_word->value);
			next_word->value = tmp;
		}
	}
}

int	special_local_var(t_cmd *cmd, t_token_list **tokens)
{
	char	*value;
	char	*tmp;

	value = (*tokens)->value;
	if (local_var(cmd, value))
	{
		tmp = add_quotes(value);
		ft_free((void **)&value);
		(*tokens)->value = tmp;
		expand_current_el(tokens, tokens);
		cmd->args[0] = (*tokens)->value;
		return (1);
	}
	return (0);
}
