#include "simple_shell.h"

/**
 * unique_error_eputs -A function that Prints a given string to the standard
 * error output.
 * @str: The string being printed.
 * Return: Absolutely nothing.
 */
void unique_error_eputs(char *str)
{
int x = 0;
if (!str)
return;
for (x = 0; str[x] != '\0'; x++)
{
unique_error_eputchar(str[x]);
}
}

/**
 * unique_error_eputchar - A function that Writes a character to
 * the standard error output.
 * @c: The character to be written.
 * Return: 1 on success, or -1 on error with appropriate errno.
 */
int unique_error_eputchar(char c)
{
static int x;
static char buf[UNIQUE_WRITE_BUFFER_SIZE];
if (c == UNIQUE_BUFFER_FLUSH || x >= UNIQUE_WRITE_BUFFER_SIZE)
{
write(2, buf, x);
x = 0;
}
if (c != UNIQUE_BUFFER_FLUSH)
{
buf[x++] = c;
}
return (1);
}
/**
 * unique_error_putfd - A function that Writes a character to the
 * specified file descriptor.
 * @c: The character to be written.
 * @file_d: The file descriptorbeing written to.
 * Return: 1 on success, or -1 on error with appropriate errno.
 */
int unique_error_putfd(char c, int file_d)
{
static int x;
static char buf[UNIQUE_WRITE_BUFFER_SIZE];
if (c == UNIQUE_BUFFER_FLUSH || x >= UNIQUE_WRITE_BUFFER_SIZE)
{
write(file_d, buf, x);
x = 0;
}
if (c != UNIQUE_BUFFER_FLUSH)
{
buf[x++] = c;
}
return (1);
}
/**
 * unique_error_putsfd - A function that Prints a given string to
 * the specified file descriptor.
 * @str: The string being printed
 * @file_d: The file descriptor to write to.
 * Return: the exact number of characters written.
 */
int unique_error_putsfd(char *str, int file_d)
{
int x = 0;
if (!str)
return (0);
for (; *str; str++)
{
x += unique_error_putfd(*str, file_d);
}
return (x);
}
