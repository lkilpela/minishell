#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int	is_whitespace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*skip_whitespaces(char *str)
{
	while (*str && is_whitespace(*str))
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	while (*str && !is_whitespace(*str) && !is_operator(*str) && !is_quote(*str))
		str++;
	return (str);
}

char *skip_op(char *str)
{
	if (is_operator(*str))
		str++;
	return (str);
}

char *skip_quote(char *str)
{
	int	in_quote = 1;

	str++;
	while (in_quote)
	{
		if (is_quote(*str))
			in_quote = 0;
		else
			str++;
	}
	if (!in_quote)
		str++;
	return (str);
}

int count_tokens(char *str)
{
	int count = 0;

	while (*str)
	{
		str = skip_whitespaces(str);
		if (*str && !is_operator(*str) && !is_quote(*str))
		{
			count++;
			str = skip_word(str);
		}
		else if (*str && is_operator(*str))
		{
			count++;
			str = skip_op(str);
		}
		else if (*str && is_quote(*str))
		{
			count++;
			str = skip_quote(str);
		}
	}
	return (count);
}

int	len_inquote(char *str)
{
	char *end;
	int len = 0;

	str++;
	end = str;
	end = skip_quote(str);
	end--;
	len = end - str;
	return (len);
}

char *find_token_end(char *str)
{
	char	*end;

	end = str;
	if (is_operator(*str))
		end++;
	else
		while (*end && !is_whitespace(*end) && !is_operator(*end))
			end++;
	return (end);
}

char	*create_a_token(char *str)
{
	char	*a_token;
	int		i;
	int		len;
	char	*end;

	
	i = 0;
	if (is_quote(*str))
	{
		len = len_inquote(str);
		str++;
	}
	else if (*str == '>' && *(str + 1) == '>')
		len = 2;
	else
	{
		end = find_token_end(str);
		len = end - str;
	}		
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

char **split_input(char *str)
{
	int	number_token = count_tokens(str);
	char **tab = malloc(sizeof(char*) * (number_token + 1));
	if (!tab)
		return (NULL);
	int i = 0;
	while (*str)
	{
		str = skip_whitespaces(str);
		if (!*str)
			break;
		if (is_quote(*str))
		{
			tab[i] = create_a_token(str);
			str = skip_quote(str);
		} 
		else
		{
			if (!is_operator(*str))
			{
				tab[i] = create_a_token(str);
				str = skip_word(str);
			}
			else
			{
				tab[i] = create_a_token(str);
				if (*str == '>' && *(str + 1) == '>')
					str++;
				str = skip_op(str);
			}
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
void	free_arrays(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
// "   echo<|grep >" -> bash: syntax error near unexpected token `|'
int main()
{
	char **tab = split_input("   echo \"Hello\" >> |ls");
	//char *str = "echo \"Hello\" |ls";
	//int count = count_tokens(str);
	//printf("count_token: %d\n", count);
	for (int i = 0; tab[i]; i++)
        printf("'%s'\n", tab[i]);
	free_arrays(tab);

	/*char *str = "\"hello\"";
	int len = len_inquote(str);
	printf("len_inquote: %d\n", len);*/
}
