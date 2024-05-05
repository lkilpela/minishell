#include <minishell.h>

int main(void)
{
	char *line;

	while (42)
	{
		line = readline("Minishell:>");
		printf("%s\n", line);
		free(line);
	}
	return (0);
}