#include "shell.h"

/**
 * find_builtin - This function confirms if the command is a builtin
 * @vars: variables
 * Return: pointer to the function or NULL
 */
void (*find_builtin(vars_t *vars))(vars_t *vars)
{
	unsigned int x;
	builtins_t check[] = {
		{"exit", exit_shell},
		{"env", print_environment},
		{"setenv", set_environment_variable},
		{"unsetenv", unset_environment_variable},
		{NULL, NULL}
	};

	for (x = 0; check[x].f != NULL; x++)
	{
		if (compare_strings(vars->arguments[0], check[x].name) == 0)
			break;
	}
	if (check[x].f != NULL)
		check[x].f(vars);
	return (check[x].f);
}

/**
 * exit_shell - A function that exits the shell
 * @vars: variables
 * Return: void
 */
void exit_shell(vars_t *vars)
{
	int pos;

	if (compare_strings(vars->arguments[0], "exit") == 0 && vars->arguments[1]
			!= NULL)
	{
		pos = convert_string_to_integer(vars->arguments[1]);
		if (pos == -1)
		{
			vars->exit_status = 2;
			print_error_message(vars, ": Illegal number: ");
			write_string_to_stderr(vars->arguments[1]);
			write_string_to_stderr("\n");
			free(vars->commands);
			vars->commands = NULL;
			return;
		}
		vars->exit_status = pos;
	}
	free(vars->command_buffer);
	free(vars->arguments);
	free(vars->commands);
	free_environment(vars->environment);
	exit(vars->exit_status);
}

/**
 * print_environment - A function that shows the current environment
 * @vars: struct of variables
 * Return: void.
 */
void print_environment(vars_t *vars)
{
	unsigned int x;

	for (x = 0; vars->environment[x]; x++)
	{
		write_string(vars->environment[x]);
		write_string("\n");
	}
	vars->exit_status = 0;
}

/**
 * set_environment_variable - A function that sets a new environment
 * variable, or edit an existing one
 * @vars: pointer to struct of variables
 * Return: void
 */
void set_environment_variable(vars_t *vars)
{
	char **key;
	char *ephem;

	if (vars->arguments[1] == NULL || vars->arguments[2] == NULL)
	{
		print_error_message(vars, ": Incorrect number of arguments\n");
		vars->exit_status = 2;
		return;
	}
	key = find_key_in_environment(vars->environment, vars->arguments[1]);
	if (key == NULL)
		add_key_value_pair(vars);
	else
	{
		ephem = append_value_to_key(vars->arguments[1], vars->arguments[2]);
		if (ephem == NULL)
		{
			print_error_message(vars, NULL);
			free(vars->command_buffer);
			free(vars->commands);
			free(vars->arguments);
			free_environment(vars->environment);
			exit(127);
		}
		free(*key);
		*key = ephem;
	}
	vars->exit_status = 0;
}

/**
 * unset_environment_variable - A function that deletes an environment variable
 * @vars: pointer to a struct of variables
 *
 * Return: void
 */
void unset_environment_variable(vars_t *vars)
{
	char **key, **cust_env;

	unsigned int x, y;

	if (vars->arguments[1] == NULL)
	{
		print_error_message(vars, ": Incorrect number of arguments\n");
		vars->exit_status = 2;
		return;
	}
	key = find_key_in_environment(vars->environment, vars->arguments[1]);
	if (key == NULL)
	{
		print_error_message(vars, ": No variable to unset");
		return;
	}
	for (x = 0; vars->environment[x] != NULL; x++)
		;
	cust_env = malloc(sizeof(char *) * x);
	if (cust_env == NULL)
	{
		print_error_message(vars, NULL);
		vars->exit_status = 127;
		exit_shell(vars);
	}
	for (x = 0; vars->environment[x] != *key; x++)
		cust_env[x] = vars->environment[x];
	for (y = x + 1; vars->environment[y] != NULL; y++, x++)
		cust_env[x] = vars->environment[y];
	cust_env[x] = NULL;
	free(*key);
	free(vars->environment);
	vars->environment = cust_env;
	vars->exit_status = 0;
}
