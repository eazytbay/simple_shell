#include "shell.h"


/**
 * tokenize_string - A function that tokenizes a buffer with a delimiter
 * @buffer: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **tokenize_string(char *buffer, char *delimiter)
{
	char **toks = NULL;
	size_t x = 0, cnt = 10;

	if (buffer == NULL)
		return (NULL);
	toks = malloc(sizeof(char *) * cnt);
	if (toks == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((toks[x] = custom_strtok(buffer, delimiter)) != NULL)
	{
		x++;
		if (x == cnt)
		{
			toks = reallocate_memory(toks, &cnt);
			if (toks == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		buffer = NULL;
	}
	return (toks);
}
