#include "shell.h"
/**
 * execute_from_path - A function that executes a command in the path
 * @command: full path to the command
 * @vars: pointer to struct of variables
 *
 * Return: 0 on succcess, 1 on failure
 */
int execute_from_path(char *command, vars_t *vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error_message(vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, vars->arguments,
						vars->environment) == -1)
				print_error_message(vars, NULL);
		}
		else
		{
			wait(&vars->exit_status);
			if (WIFEXITED(vars->exit_status))
				vars->exit_status = WEXITSTATUS(vars->exit_status);
			else if (WIFSIGNALED(vars->exit_status) &&
					WTERMSIG(vars->exit_status) == SIGINT)
				vars->exit_status = 130;
			return (0);
		}
		vars->exit_status = 127;
		return (1);
	}
	else
	{
		print_error_message(vars, ": Permission denied\n");
		vars->exit_status = 126;
	}
	return (0);
}
/**
 * find_executable_path - A function that finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_executable_path(char **env)
{
	char *wy = "PATH=";
	unsigned int x, y;

	for (x = 0; env[x] != NULL; x++)
	{
		for (y = 0; y < 5; y++)
			if (wy[y] != env[x][y])
				break;
		if (y == 5)
			break;
	}
	return (env[x]);
}
/**
 * search_for_executable_in_path - A function that checks if the
 * command is in the PATH
 * @vars: variables
 *
 * Return: void
 */
void search_for_executable_in_path(vars_t *vars)
{
char *wy, *dup_path = NULL, *loc = NULL;
unsigned int x = 0, y = 0, char **path_tokens, struct stat buf;

	if (check_for_directory(vars->arguments[0]))
		y = execute_from_current_directory(vars);
	else
	{
		wy = find_executable_path(vars->environment);
		if (wy != NULL)
		{
			dup_path = duplicate_string(wy + 5);
			path_tokens = tokenize_string(dup_path, ":");
			for (x = 0; path_tokens && path_tokens[x]; x++, free(loc))
			{
				loc = concatenate_strings(path_tokens[x],
						vars->arguments[0]);
				if (stat(loc, &buf) == 0)
				{
					y = execute_from_path(loc, vars);
					free(loc);
					break;
				}
			}
			free(dup_path);
			if (path_tokens == NULL)
			{
				vars->exit_status = 127;
				exit_shell(vars);
			}
		}
		if (wy == NULL || path_tokens[x] == NULL)
		{
			print_error_message(vars, ": not found\n");
			vars->exit_status = 127;
		}
		free(path_tokens);
	}
	if (y == 1)
		exit_shell(vars);
}
/**
 * execute_from_current_directory - A function executes the command in the
 * current working directory
 * @vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */
int execute_from_current_directory(vars_t *vars)
{
	pid_t child_pid, struct stat buf;

	if (stat(vars->arguments[0], &buf) == 0)
	{
		if (access(vars->arguments[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error_message(vars, NULL);
			if (child_pid == 0)
			{
				if (execve(vars->arguments[0], vars->arguments,
							vars->environment) == -1)
					print_error_message(vars, NULL);
			}
			else
			{
				wait(&vars->exit_status);
				if (WIFEXITED(vars->exit_status))
					vars->exit_status = WEXITSTATUS(vars->exit_status);
				else if (WIFSIGNALED(vars->exit_status) &&
						WTERMSIG(vars->exit_status) == SIGINT)
					vars->exit_status = 130;
				return (0);
			}
			vars->exit_status = 127;
			return (1);
		}
		else
		{
			print_error_message(vars, ": Permission denied\n");
			vars->exit_status = 126;
		}
		return (0);
	}
	print_error_message(vars, ": not found\n");
	vars->exit_status = 127;
	return (0);
}
/**
 * check_for_directory - A function that checks if the command is a
 * part of a path
 * @str: command
 *
 * Return: 1 on success, 0 on failure
 */
int check_for_directory(char *str)
{
	unsigned int x;

	for (x = 0; str[x]; x++)
	{
		if (str[x] == '/')
			return (1);
	}
	return (0);
}
