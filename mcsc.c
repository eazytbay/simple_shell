#include "simple_shell.h"
/**
 * custom_shell_gen_interactive - A function that returns a true value if the
 * shell is in interactive mode
 * @sa: The address of the struct
 * Return: if the shell in in interactive mode, return 1 and 0 if not
 */
int custom_shell_gen_interactive(unique_info_t *sa)
{
return (isatty(STDIN_FILENO) && sa->custom_read_file_descriptor <= 2);
}
/**
 * unique_delim - A function that confirms if a character is a delimeter
 * @ch: the char to check
 * @del: the string's delimeter
 * Return: The value 1 if the character is a delimeter and 0 if it's not
 */
int unique_delim(char ch, char *del)
{
for (; *del != '\0'; del++)
{
if (*del == ch)
return (1);
}
return (0);
}
/**
 * custom_gen_shell_alpha -  A function that looks out for an
 * alphabetic character
 * @ch: The inputed character or the character being inputed
 * Return: if the character is alphabetic, return 1 and 0 if it is not.
 */
int custom_gen_shell_alpha(int ch)
{
if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
return (1);
else
return (0);
}
/**
 * custom_gen_shell_atoi - Functions as string converter to an integer
 * @st: the expected string that's to be converted
 * Return: if there are no numbers present in the string, return 0 and on
 * success return the  converted string.
 */
int custom_gen_shell_atoi(char *st)
{
int x = 0, mk = 1, sy = 0, o;
unsigned int rslt = 0;
while (st[x] != '\0' && sy != 2)
{
if (st[x] == '-')
mk *= -1;
if (st[x] >= '0' && st[x] <= '9')
{
sy = 1;
rslt *= 10;
rslt += (st[x] - '0');
}
else if (sy == 1)
sy = 2;
x++;
}
if (mk == -1)
o = -rslt;
else
o = rslt;
return (o);
}
