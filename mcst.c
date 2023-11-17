#include "simple_shell.h"
/**
 * custom_gen_strtow - A function that divides a string into word ignoring del
 * @ins: the string to be inputed
 * @del: the string's delimter
 * Return: On success, a pointer to an array of strings, on failure, NULL
 */
char **custom_gen_strtow(char *ins, char *del)
{
int x = 0, y = 0, z = 0, a = 0, nw = 0;
char **c;
if (ins == NULL || ins[0] == 0)
return (NULL);
if (!del)
del = " ";
while (ins[x] != '\0')
{
if (!unique_delim(ins[x], del) && (unique_delim(ins[x + 1], del)
|| !ins[x + 1]))
nw++;
x++;
}
if (nw == 0)
return (NULL);
c = malloc((1 + nw) *sizeof(char *));
if (!c)
return (NULL);
while (y < nw)
{
while (unique_delim(ins[x], del))
x++;
while (!unique_delim(ins[x + z], del) && ins[x + z])
z++;
c[y] = malloc((z + 1) * sizeof(char));
if (!c[y])
{
for (z = 0; z < y; z++)
free(c[z]);
free(c);
return (NULL);
}
for (a = 0; a < z; a++)
{
c[y][a] = ins[x++];
}
c[y][a] = 0;
}
c[y] = NULL;
return (c);
}
/**
 * custom_gen_sstrtow - A function that divides a string into words
 * @ins: the string being inputed
 * @del: the delimeter
 *  Return: On success, a pointer to an array of strings, on failure, NULL
 */
char **custom_gen_sstrtow(char *ins, char del)
{
int x = 0, y = 0, z = 0, a = 0, nw = 0;
char **c;
if (ins == NULL || ins[0] == 0)
return (NULL);
while (ins[x] != '\0')
{
if ((ins[x] != del && ins[x + 1] == del) ||
(ins[x] != del && !ins[x + 1]) || ins[x + 1] == del)
nw++;
x++;
}
if (nw == 0)
return (NULL);
c = malloc((1 + nw) *sizeof(char *));
if (!c)
return (NULL);
while (y < nw)
{
while (ins[x] == del && ins[x] != del)
x++;
while (ins[x + z] != del && ins[x + z] && ins[x + z] != del)
z++;
c[y] = malloc((z + 1) * sizeof(char));
if (!c[y])
{
for (z = 0; z < y; z++)
free(c[z]);
free(c);
return (NULL);
}
while (a < z)
{
c[y][a] = ins[x++];
a++;
}
c[y][a] = 0;
y++;
}
c[y] = NULL;
return (c);
}
