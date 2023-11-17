#include "simple_shell.h"

/**
 * custom_gen_strlen - A function that Calculate the length of a string.
 * @str: The string to be evaluated.
 * Return: The length of the evaluated string.
 */
int custom_gen_strlen(char *str)
{
int x = 0;
if (!str)
return (0);
for (; *str; str++)
{
x++;
}
return (x);
}
/**
 * custom_gen_strcmp - A function that Compares two strings
 * @str1: string 1.
 * @str2: string 2
 * Return: A Negative value as long as str1 < str2, positive value
 * as long str1 > str2 and zero if str1 == str2.
 */
int custom_gen_strcmp(char *str1, char *str2)
{
for (; *str1 && *str2; str1++, str2++)
{
if (*str1 != *str2)
return (*str1 - *str2);
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}
/**
 * custom_gen_starts - A function that Checks if a string
 * starts with a specified substring.
 * @hs: The string being searched.
 * @substr: The substring being located
 * Return: On success, the exact Address of the character that follows in
 * hs or NULL on failure.
 */
char *custom_gen_starts(const char *hs, const char *substr)
{
for (; *substr; substr++, hs++)
{
if (*substr != *hs)
return (NULL);
}
return ((char *)hs);
}
/**
 * custom_gen_strcat - A function that mimics the strcat function to
 * Concatenate two strings.
 * @db: The buffer's destination.
 * @sb: The buffer's source.
 * Return: Pointer to the db.
 */
char *custom_gen_strcat(char *db, char *sb)
{
char *r = db;
for (; *db; db++)
for (; *sb; db++, sb++)
{
*db = *sb;
}
*db = *sb;
return (r);
}
