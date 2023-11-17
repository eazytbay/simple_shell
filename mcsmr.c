#include "simple_shell.h"

/**
 * custom_shell_memset - A function that fills memory with
 * a byte that is constant
 * @ptr: the pointer to the memory area
 * @bt: the byte to fill *s with
 * @am: the ammplitude of bytes to be filled
 * Return: The pointer to filled memory area
 */
char *custom_shell_memset(char *ptr, char bt, unsigned int am)
{
unsigned int x = 0;
while (x < am)
{
ptr[x] = bt;
x++;
}
return (ptr);
}
/**
 * custom_shell_ffree - A function that liberates a collection of string
 * @sos: string array to be liberated
 */
void custom_shell_ffree(char **sos)
{
char **x = sos;
if (!sos)
return;
for (; *sos; free(*sos++))
;
free(x);
}
/**
 * custom_shell_realloc - Adjust the size of a memory block
 * @ptr: pointer to the previously allocated memory block
 * @os: size of previous block in bytes
 * @ns: size of the new memory block in bytes
 * Return: The pointer to the reallocated memory block
 */
void *custom_shell_realloc(void *ptr, unsigned int os, unsigned int ns)
{
char *x;
if (!ptr)
return (malloc(ns));
if (!ns)
return (free(ptr), NULL);
if (ns == os)
return (ptr);
x = malloc(ns);
if (!x)
return (NULL);
os = os < ns ? os : ns;
for (; os > 0; os--)
x[os - 1] = ((char *)x)[os - 1];
free(ptr);
return (x);
}
