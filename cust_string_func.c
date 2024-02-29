#include "shell.h"

/**
 * write_string -  This function writes a string to stdout
 * @str: string to write
 *
 * Return: number of chars printed or -1 on failure
 */
ssize_t write_string(char *str)
{
	ssize_t dig, length;

	dig = string_length(str);
	length = write(STDOUT_FILENO, str, dig);
	if (length != dig)
	{
		perror("Fatal Error");
		return (-1);
	}
	return (length);
}

/**
 * duplicate_string - A function that returns pointer to new mem alloc space
 * which contains copy
 * @strtodup: string to be duplicated
 * Return: a pointer to the new duplicated string
 */
char *duplicate_string(char *strtodup)
{
	char *dup;

	int length, x;

	if (strtodup == 0)
		return (NULL);

	for (length = 0; strtodup[length]; length++)
		;
	dup = malloc((length + 1) * sizeof(char));

	for (x = 0; x <= length; x++)
		dup[x] = strtodup[x];

	return (dup);
}

/**
 * compare_strings - A function that compares two strings
 * @strcmp1: first string, of two, to be compared in length
 * @strcmp2: second string, of two, to be compared
 * Return: 0 on success, anything else is a failure
 */
int compare_strings(char *strcmp1, char *strcmp2)
{
	int x;

	x = 0;
	while (strcmp1[x] == strcmp2[x])
	{
		if (strcmp1[x] == '\0')
			return (0);
		x++;
	}
	return (strcmp1[x] - strcmp2[x]);
}

/**
 * concatenate_strings - This function concatenates two strings
 * @strc1: first string
 * @strc2: second string
 * Return: pointer
 */
char *concatenate_strings(char *strc1, char *strc2)
{
	char *fr_string;
	unsigned int length1, length2, fr_len, x, y;

	length1 = 0;
	length2 = 0;
	if (strc1 == NULL)
		length1 = 0;
	else
	{
		for (length1 = 0; strc1[length1]; length1++)
			;
	}
	if (strc2 == NULL)
		length2 = 0;
	else
	{
		for (length2 = 0; strc2[length2]; length2++)
			;
	}
	fr_len = length1 + length2 + 2;
	fr_string = malloc(fr_len * sizeof(char));
	if (fr_string == NULL)
		return (NULL);
	for (x = 0; x < length1; x++)
		fr_string[x] = strc1[x];
	fr_string[x] = '/';
	for (y = 0; y < length2; y++)
		fr_string[x + 1 + y] = strc2[y];
	fr_string[length1 + length2 + 1] = '\0';
	return (fr_string);
}

/**
 * string_length - This function returns the length of a string
 * @str: string to be measured
 * Return: length of string
 */
unsigned int string_length(char *str)
{
	unsigned int length;

	length = 0;

	for (length = 0; str[length]; length++)
		;
	return (length);
}
