#include "simple_shell.h"
/**
 * unique_shell_cmd - A function that checks the executability of a file
 * @stinf: The information 
 * @abs: the absolute or relative path to the file being checked
 * Return: 1 if the file is executable and 0 if not.
 */
int unique_shell_cmd(unique_info_t *stinf, char *abs)
{
struct stat st;
(void)stinf;
if (!abs || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
 * unique_shell_char_dup - A function that can duplicates characters
 * @strdir: the PATH string
 * @begin: The beginning
 * @end: the very end
 * Return: pointer to a new buffer that has been specified
 */
char *unique_shell_char_dup(char *strdir, int begin, int end)
{
static char buffer[1024];
int x = 0, y = 0;
while (x >= begin && x < end)
{
if (strdir[x] != ':')
buffer[y++] = strdir[x];
x++;
}
buffer[y] = 0;
return (buffer);
}
/**
 * unique_shell_path_loc -  A function that locates the cmd in the string PATH
 * @st: The information
 * @strpat: the expeted PATH of the string
 * @cmd: the cmd to be located
 * Return: cmd full path
 */
char *unique_shell_path_loc(unique_info_t *info, char *strpat, char *cmd)
{
int x = 0, pp = 0;
char *path;
if (!strpat)
return (NULL);
if ((custom_gen_strlen(cmd) > 2) && custom_gen_strncmp(cmd, "./", 2) == 0)
{
if (unique_shell_cmd(st, cmd))
return (cmd);
}
for (; ; x++)
{
if (!strpat[x] || strpat[x] == ':')
{
path = unique_shell_char_dup(strpat, pp, x);
if (!*path)
custom_gen_strcat(path, cmd);
else
{
custom_gen_strcat(path, "/");
custom_gen_strcat(path, cmd);
}
if (unique_shell_cmd(st, path))
return (path);
if (!strpat[x])
break;
pp = x;
}
}
return (NULL);
}
