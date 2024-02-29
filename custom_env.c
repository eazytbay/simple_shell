#include "shell.h"

/**
 * duplicate_environment - This function duplicates the shell environment
 * @env: environment passed to main
 *
 * Return: pointer to the new environment
 */
char **duplicate_environment(char **env)
{
char **cust_env = NULL;
size_t x = 0;

while (env[x] != NULL)
x++;

cust_env = malloc(sizeof(char *) * (x + 1));
if (cust_env == NULL)
{
perror("Fatal Error");
exit(1);
}

x = 0;
while (env[x] != NULL)
{
cust_env[x] = duplicate_string(env[x]);
x++;
}
cust_env[x] = NULL;

return (cust_env);
}

/**
 * free_environment - A function that frees the environment of the shell
 * @env: shell's environment
 *
 * Return: void
 */
void free_environment(char **env)
{
	unsigned int x;

	for (x = 0; env[x] != NULL; x++)
		free(env[x]);
	free(env);
}
