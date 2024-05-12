#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}



char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str) && !is_operator(*str))
		str++;
	return (str);
}

char *skip_op(char *str)
{
	while (*str && is_operator(*str))
		str++;
	return (str);
}

int count_tokens(char *str)
{
	int count = 0;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (*str && !is_operator(*str))
		{
			count++;
			str = skip_word(str);
		}
		else if (*str && is_operator(*str))
		{
			count++;
			str = skip_op(str);
		}
	}
	return count;
}

char	*create_a_token(char *str)
{
	char	*a_token;
	int		i;
	int		len;
	char	*end;

	end = str;
	i = 0;
	if (is_operator(*str))
		end++;
	else
		while (*end && !is_whitespace(*end) && !is_operator(*end))
			end++;
	len = end - str;
	a_token = malloc(sizeof(char) * (len + 1));
	if (!a_token)
		return (NULL);
	while (i < len)
	{
		a_token[i] = str[i];
		i++;
	}
	a_token[len] = '\0';
	return (a_token);

}

char **split_token(char *str)
{
	int	number_token = count_tokens(str);
	char **tab = malloc(sizeof(char*) * (number_token + 1));
	if (!tab)
		return (NULL);
	int i = 0;
	while (*str)
	{
		str = skip_whitespaces(str);
		if(!*str)
			continue;
		if (!is_operator(*str))
			str = skip_word(str);
		else
			str = skip_op(str);
		tab[i] = create_a_token(str);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
void	free_arrays(char **arrays)
{
	int	i;

	i = 0;
	while (arrays[i])
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}

int main()
{
	char **tab = split_token("echo| grep");
	//int count = count_tokens(str);
	//printf("count_token: %d\n", count);
	for (int i = 0; tab[i]; i++)
        printf("'%s'\n", tab[i]);
	free_arrays(tab);
}
