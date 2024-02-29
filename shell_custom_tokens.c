#include "shell.h"

/**
 * find_match - This function checks if a character matches any in a string
 * @c: character to check
 * @str: string to check
 *
 * Return: 1 if match, 0 if not
 */
unsigned int find_match(char c, const char *str)
{
unsigned int x = 0;

while (str[x] != '\0')
{
if (c == str[x])
return (1);
x++;
}
return (0);
}

/**
 * custom_strtok -A function that tokenizes the string
 * @str: string to tokenize
 * @delim: delimiter to tokenize against
 *
 * Return: pointer to the next token or NULL
 */
char *custom_strtok(char *str, const char *delim)
{
static char *beg_token;
static char *ffg_token;
unsigned int x = 0;
if (str != NULL)
ffg_token = str;
beg_token = ffg_token;
if (beg_token == NULL)
return (NULL);
while (ffg_token[x] != '\0')
{
if (find_match(ffg_token[x], delim) == 0)
break;
x++;
}
if (ffg_token[x] == '\0' || ffg_token[x] == '#')
{
ffg_token = NULL;
return (NULL);
}
beg_token = ffg_token + x;
ffg_token = beg_token;
x = 0;
while (ffg_token[x] != '\0')
{
if (find_match(ffg_token[x], delim) == 1)
break;
x++;
}
if (ffg_token[x] == '\0')
ffg_token = NULL;
else
{
ffg_token[x] = '\0';
ffg_token = ffg_token + x + 1;
if (*ffg_token == '\0')
ffg_token = NULL;
}
return (beg_token);
}
