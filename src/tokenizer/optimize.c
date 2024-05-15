/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:18:16 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/15 10:27:01 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *next_token(char *str)
{
	while (*str)
	{
		if (is_whitespace(*str))
			str = skip_whitespaces(str);
		else if (is_word(*str))
			str = skip_word(str);
		else if (is_operator(*str))
			str = skip_op(str);
		else if (is_quote(*str))
			str = skip_quote(str);
		else if (*str == '$')
			str = skip_variable(str);
		else
			break;
	}
	return (str);
}