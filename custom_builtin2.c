#include "shell.h"

/**
 * add_key_value_pair - A function that creates a new environment variable
 * @vars:This pointer points to the struct of the variables
 *
 * Return: void
 */
void add_key_value_pair(vars_t *vars)
{
unsigned int x = 0;
char **cust_env;
while (vars->environment[x] != NULL)
x++;
cust_env = malloc(sizeof(char *) * (x + 2));
if (cust_env == NULL)
{
print_error_message(vars, NULL);
vars->exit_status = 127;
exit_shell(vars);
}
x = 0;
while (vars->environment[x] != NULL)
{
cust_env[x] = vars->environment[x];
x++;
}
cust_env[x] = append_value_to_key(vars->arguments[1], vars->arguments[2]);
if (cust_env[x] == NULL)
{
print_error_message(vars, NULL);
free(vars->command_buffer);
free(vars->commands);
free(vars->arguments);
free_environment(vars->environment);
free(cust_env);
exit(127);
}
cust_env[x + 1] = NULL;
free(vars->environment);
vars->environment = cust_env;
}

/**
 * find_key_in_environment - A function that finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_key_in_environment(char **env, char *key)
{
	unsigned int x, y, en;

	en = string_length(key);
	for (x = 0; env[x] != NULL; x++)
	{
		for (y = 0; y < en; y++)
			if (key[y] != env[x][y])
				break;
		if (y == en && env[x][y] == '=')
			return (&env[x]);
	}
	return (NULL);
}

/**
 * append_value_to_key - A function that creates a new
 * environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *append_value_to_key(char *key, char *value)
{
	unsigned int en1, en2, x, y;
	char *fr;

	en1 = string_length(key);
	en2 = string_length(value);
	fr = malloc(sizeof(char) * (en1 + en2 + 2));
	if (fr == NULL)
		return (NULL);
	for (x = 0; key[x] != '\0'; x++)
		fr[x] = key[x];
	fr[x] = '=';
	for (y = 0; value[y] != '\0'; y++)
		fr[x + 1 + y] = value[y];
	fr[x + 1 + y] = '\0';
	return (fr);
}

/**
 * convert_string_to_integer - A function that converts a
 * string into an integer
 * @str: string to convert
 * Return: the integer value, or -1 if an error occurs
 */
int convert_string_to_integer(char *str)
{
	unsigned int x, val;
	int number = 0, test_number;

	test_number = INT_MAX;
	for (val = 0; test_number != 0; val++)
		test_number /= 10;
	for (x = 0; str[x] != '\0' && x < val; x++)
	{
		number *= 10;
		if (str[x] < '0' || str[x] > '9')
			return (-1);
		if ((x == val - 1) && (str[x] - '0' > INT_MAX % 10))
			return (-1);
		number += str[x] - '0';
		if ((x == val - 2) && (str[x + 1] != '\0') && (number > INT_MAX / 10))
			return (-1);
	}
	if (x > val)
		return (-1);
	return (number);
}
