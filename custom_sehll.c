#include "shell.h"
/* This is global variable that handles ^C*/
unsigned int flag_signal;

/**
 * sig_handler - This function handles signal interupt of C
 * @uuv: This is an unused variable which is required for signal
 * function prototype
 *
 * Return: void
 */
static void sig_handler(int uuv)
{
	(void) uuv;
	if (flag_signal == 0)
		write_string("\n$ ");
	else
		write_string("\n");
}

/**
 * main - The entry point and main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t buffer_length = 0;
	unsigned int is_pipe = 0, x;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	vars.initial_arguments = argv;
	vars.environment = duplicate_environment(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		write_string("$ ");
	flag_signal = 0;
	while (getline(&(vars.command_buffer), &buffer_length, stdin) != -1)
	{
		flag_signal = 1;
		vars.command_count++;
		vars.commands = tokenize_string(vars.command_buffer, ";");
		for (x = 0; vars.commands && vars.commands[x] != NULL; x++)
		{
			vars.arguments = tokenize_string(vars.commands[x], "\n \t\r");
			if (vars.arguments && vars.arguments[0])
				if (find_builtin(&vars) == NULL)
					search_for_executable_in_path(&vars);
			free(vars.arguments);
		}
		free(vars.command_buffer);
		free(vars.commands);
		flag_signal = 0;
		if (is_pipe == 0)
			write_string("$ ");
		vars.command_buffer = NULL;
	}
	if (is_pipe == 0)
		write_string("\n");
	free_environment(vars.environment);
	free(vars.command_buffer);
	exit(vars.exit_status);
}
