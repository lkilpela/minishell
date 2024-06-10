/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aklein <aklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:03:33 by lkilpela          #+#    #+#             */
/*   Updated: 2024/06/10 10:51:22 by aklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_for_ending(char *str, int len)
{
	if (is_operator(*str) || is_double_operator(str) || !is_word(*str))
	{
		if (len > 0)
			return (len);
		if (is_double_operator(str))
			return (2);
		return (1);
	}
	return (0);
}

int	token_len(char *str)
{
	char	inquote;
	int		len;
	int		end;

	len = 0;
	inquote = 0;
	while (*str)
	{
		if (is_quote(*str))
		{
			if (inquote == 0)
				inquote = *str;
			else if (inquote == *str)
				inquote = 0;
		}
		else if (!inquote)
		{
			end = check_for_ending(str, len);
			if (end > 0)
				return (end);
		}
		len++;
		str++;
	}
	return (len);
}

static t_token_type	get_token_type(char *str)
{
	if (!ft_strncmp(str, "<<", 2))
		return (OP_DLESS);
	else if (!ft_strncmp(str, ">>", 2))
		return (OP_DGREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '<')
		return (OP_LESS);
	else if (*str == '>')
		return (OP_GREAT);
	else if (*str == '|')
		return (OP_PIPE);
	else
		return (WORD);
}

void	extract_token(char *str, char **value, t_token_type *type)
{
	int	len;

	len = token_len(str);
	*value = ft_safe_strndup(str, len);
	*type = get_token_type(str);
}
