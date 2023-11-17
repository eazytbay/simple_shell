#include "simple_shell.h"
/**
 * custom_gen_strcpy - A function that Copies a string.
 * @db: The buffer's destination.
 * @ss: The string's source.
 * Return: Pointer to the db.
 */
char *custom_gen_strcpy(char *db, char *ss)
{
int x = 0;
if (db == ss || ss == 0)
return (db);
for (; ss[x]; x++)
{
db[x] = ss[x];
}
db[x] = 0;
return (db);
}
/**
 * custom_gen_strdup - A function that makes a  Duplicate of  a string.
 * @ds: The string being duplicated.
 * Return: the Pointer to ds.
 */
char *custom_gen_strdup(const char *ds)
{
int len = 0;
char *r;
if (ds == NULL)
return (NULL);
for (; *ds; ds++)
{
len++;
}
r = malloc(sizeof(char) * (len + 1));
if (!r)
return (NULL);
for (len++; len--;)
{
r[len] = *--ds;
}
return (r);
}
/**
 * custom_gen_puts -A function that outputs an input string.
 * @ps: The string being displayed.
 * Return: Absloutely Nothing.
 */
void custom_gen_puts(char *ps)
{
int x;
if (!ps)
return;
for (x = 0; ps[x] != '\0'; x++)
{
custom_gen_putchar(ps[x]);
}
}

/**
 * custom_gen_putchar - A function that ensures
 * the character c is written to stdout.
 * @ch: The expected character to be written.
 * Return: 1 on success,
 * return -1 on error and set the errno rightly
 */
int custom_gen_putchar(char ch)
{
static int x;
static char buf[UNIQUE_WRITE_BUFFER_SIZE];
if (ch == UNIQUE_BUFFER_FLUSH || x >= UNIQUE_WRITE_BUFFER_SIZE)
{
write(1, buf, x);
x = 0;
}
if (ch != UNIQUE_BUFFER_FLUSH)
{
buf[x++] = ch;
}
return (1);
}
