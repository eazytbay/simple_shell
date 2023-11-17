#include "simple_shell.h"
/**
 * unique_terminal - The Main function for the custom shell's main loop.
 * @st: the parameter & return info struct
 * @avect: the vector's main argument
 * Return: 0 when successful, 1 should there be an error
 */
int unique_terminal(unique_info_t *st, char **avect)
{
ssize_t x = 0;
int br = 0;
for (; x != -1 && br != -2;)
{
custom_clr_inf(st);
if (custom_shell_gen_interactive(st))
custom_gen_puts("$ ");
unique_error_eputchar(UNIQUE_BUFFER_FLUSH);
x = custom_read_input(st);
if (x != -1)
{
custom_shell_info_set(st, avect);
br = unique_shell_builtin(st);
if (br == -1)
unique_shell_find_cmd(st);
}
else if (custom_shell_gen_interactive(st))
custom_gen_putchar('\n');
custom_shell_info_free(st, 0);
}
custom_show_hist(st);
custom_shell_info_free(st, 1);
if (!custom_shell_gen_interactive(st) && st->custom_execution_status)
exit(st->custom_execution_status);
if (br == -2)
{
if (st->miscal_dig == -1)
exit(st->custom_execution_status);
exit(st->miscal_dig);
}
return (br);
}
/**
 * unique_shell_builtin - A function that locates a builtin command
 * @st: Doubles as the parameter &  the return info structure
 * Return: -1 should the builtin be missing,
 * 0 if the builtin command executes successfully,
 * in a case when the builtin command fails, return 1,
 * And -2 in a case whereby the builtin signals exit()
 */
int unique_shell_builtin(unique_info_t *st)
{
int x, br = -1;
unique_builtin_table builtintbl[] = {
{"exit", eazy_exit},
{"env", custom_eazy_env},
{"help", eazy_help},
{"history", eazy_history},
{"setenv", custom_eazy_setenv},
{"unsetenv", custom_eazy_remenv},
{"cd", eazy_cd},
{"alias", eazy_alias},
{NULL, NULL}
};
while (builtintbl[x].knd)
{
if (custom_gen_strcmp(st->custom_arguments[0], builtintbl[x].knd) == 0)
{
st->custom_error_count++;
br = builtintbl[x].func(st);
break;
}
x++;
}
return (br);
}
/**
 * unique_shell_find_cmd - A function that locates a command in PATH
 * @st: Doubles as the parameter & the return info struct
 * Return: void
 */
void unique_shell_find_cmd(unique_info_t *st)
{
char *custom_command_path = NULL;
int x, y;
st->custom_command_path = st->custom_arguments[0];
if (st->custom_line_count_flag == 1)
{
st->custom_error_count++;
st->custom_line_count_flag = 0;
}
for (x = 0, y = 0; st->custom_argument[x]; x++)
if (!unique_delim(st->custom_argument[x], " \t\n"))
y++;
if (!y)
return;
custom_command_path = unique_shell_path_loc(st, unique_gen_getenv
(st, "PATH="), st->custom_arguments[0]);
if (custom_command_path)
{
st->custom_command_path = custom_command_path;
unique_shell_fork_cmd(st);
}
else
{
if ((custom_shell_gen_interactive(st) || unique_gen_getenv(st, "PATH=")
|| st->custom_arguments[0][0] == '/') && unique_shell_cmd(st,
st->custom_arguments[0]))
unique_shell_fork_cmd(st);
else if (*(st->custom_argument) != '\n')
{
st->custom_execution_status = 127;
custom_shell_disp_error(st, "not found\n");
}
}
}
/**
 * unique_shell_fork_cmd - A function that that runs a cmd by
 * forking an exec threa
 * @st: Doubles as the parameter & the return info struct
 * Return: void
 */
void unique_shell_fork_cmd(unique_info_t *st)
{
pid_t new_pid;
new_pid = fork();
if (new_pid == -1)
{
perror("Error:");
return;
}
if (new_pid == 0)
{
if (execve(st->custom_command_path, st->custom_arguments,
custom_fetch_env(st)) == -1)
{
custom_shell_info_free(st, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
else
{
wait(&(st->custom_execution_status));
if (WIFEXITED(st->custom_execution_status))
{
st->custom_execution_status = WEXITSTATUS(st->custom_execution_status);
if (st->custom_execution_status == 126)
custom_shell_disp_error(st, "Error! Try again\n");
}
}
}
}
