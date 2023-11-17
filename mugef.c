#include "simple_shell.h"

/**
 * custom_gen_strncpy - A function that duplicates a string
 * @ds: the string's destination
 * @ss: the string's source
 * @f: the frequency in which the characters is to be copied
 * Return: the string that has been concantenated
 */
char *custom_gen_strncpy(char *ds, char *ss, int f)
{
char *s = ds;
int x;
int y;
for (x = 0; ss[x] != '\0' && x < f - 1; x++)
{
ds[x] = ss[x];
}
if (x < f)
{
for (y = x; y < f; y++)
{
ds[y] = '\0';
}
}
return (s);
}

/**
 * custom_gen_strncat - A function that concatenates two strings
 * @ds: string 1
 * @ss: string 2
 * @num: the number of bytes to be used at most
 * Return: the string that has been concatenated.
 */
char *custom_gen_strncat(char *ds, char *ss, int num)
{
char *s = ds;
int x;
int y;
for (x = 0; ds[x] != '\0'; x++)
{
}
for (y = 0; ss[y] != '\0' && y < num; y++)
{
ds[x] = ss[y];
x++;
}
if (y < num)
{
ds[x] = '\0';
}
return (s);
}
/**
 * custom_gen_strchr - A function that finds a character in a string
 * @str: the string in which that character is to be located from
 * @ch: the character being located
 * Return: memory area's pointer
 */
char *custom_gen_strchr(char *str, char ch)
{
do {
if (*str == ch)
return (str);
} while (*str++ != '\0');
return (NULL);
}
