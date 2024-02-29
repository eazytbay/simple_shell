#include "shell.h"

/**
 * _reallocate_memory - A function that reallocates a pointer to
 * double the space
 * @ptr: points to the old array
 * @size: Acts as pointer that points to the number of elements
 * in the old array
 * Return: pointer to the new array
 */
char **_reallocate_memory(char **ptr, size_t *size)
{
	char **fr;
	size_t x;

	fr = malloc(sizeof(char *) * ((*size) + 10));
	if (fr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (x = 0; x < (*size); x++)
	{
		fr[x] = ptr[x];
	}
	*size += 10;
	free(ptr);
	return (fr);
}
