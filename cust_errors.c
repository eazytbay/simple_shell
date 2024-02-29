#include "shell.h"

/**
 * print_error_message - A function that prints error messages to stderr
 * @vars: pointer to struct of variables
 * @msg: message to print
 *
 * Return: void
 */
void print_error_message(vars_t *vars, char *msg)
{
char *cnt;

write_string_to_stderr(vars->initial_arguments[0]);
write_string_to_stderr(": ");
cnt = convert_unsigned_integer_to_string(vars->command_count);
write_string_to_stderr(cnt);
free(cnt);
write_string_to_stderr(": ");
write_string_to_stderr(vars->arguments[0]);
if (msg)
{
write_string_to_stderr(msg);
}
else
perror("");
}

/**
 * write_string_to_stderr - A function that prints a string to stderr
 * @str: string to print
 *
 * Return: void
 */
void write_string_to_stderr(char *str)
{
	ssize_t dig, x;

	dig = string_length(str);
	x = write(STDERR_FILENO, str, dig);
	if (x != dig)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * convert_unsigned_integer_to_string - A function that converts an unsigned
 * int to a string
 * @count: unsigned int to convert
 *
 * Return: pointer to the converted string
 */
char *convert_unsigned_integer_to_string(unsigned int count)
{
	char *x;
	unsigned int ephem, digits;

	ephem = count;
	for (digits = 0; ephem != 0; digits++)
		ephem /= 10;
	x = malloc(sizeof(char) * (digits + 1));
	if (x == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	x[digits] = '\0';
	for (--digits; count; --digits)
	{
		x[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (x);
}
