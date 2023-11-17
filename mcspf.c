#include "simple_shell.h"
/**
 * unique_shell_cmd - A function that checks the executability of a file
 * @info: The information 
 * @path: the absolute or relative path to the file being checked
 * Return: 1 if the file is executable and 0 if not.
 */
int unique_shell_cmd(unique_info_t *info, char *path)
{
struct stat st;
(void)info;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}
/**
 * unique_shell_char_dup - A function that can duplicates characters
 * @pathstr: the PATH string
 * @begin: The beginning
 * @end: the very end
 * Return: pointer to a new buffer that has been specified
 */
char *unique_shell_char_dup(char *pathstr, int begin, int end)
{
static char buffer[1024];
int x = 0, y = 0;
while (x >= begin && x < end)
{
if (pathstr[x] != ':')
buffer[y++] = pathstr[x];
x++;
}
buffer[y] = 0;
return (buffer);
}
/**
 * unique_shell_path_loc -  A function that locates the cmd in the string PATH
 * @info: The information
 * @strpat: the expeted PATH of the string
 * @cmd: the cmd to located
 * Return: full path of cmd when its found or return  NULL if not
 */
char *unique_shell_path_loc(unique_info_t *info, char *strpat, char *cmd)
{
int x = 0, pp = 0;
char *path;
if (!strpat)
return (NULL);
if ((strlen(cmd) > 2) && strncmp(cmd, "./", 2) == 0)
{
if (unique_shell_cmd(info, cmd))
return (cmd);
}
for (; ; x++)
{
if (!strpat[x] || strpat[x] == ':')
{
path = unique_shell_char_dup(strpat, pp, x);
if (!*path)
strcat(path, cmd);
else
{
strcat(path, "/");
strcat(path, cmd);
}
if (unique_shell_cmd(info, path))
return (path);
if (!strpat[x])
break;
pp = x;
}
}
return (NULL);
}
