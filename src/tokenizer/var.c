/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:44 by lkilpela          #+#    #+#             */
/*   Updated: 2024/05/14 22:55:10 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <tokenizer.h>
#include <stdlib.h>
#include <stdio.h>

//void	expand_variables(char *str)
int main()
{
	char *var_value;
	const char *var_name = "USER";

	var_value = getenv(var_name);
	printf("var_value: %s\n", var_value);
}

