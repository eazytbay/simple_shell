#include "simple_shell.h"
/**
 * custom_shell_errorem -  A function that changes a string to an integer
 * @is: the input string being converted
 * Return: 0 if numeric characters are found and -1 if not.
 */
int custom_shell_errorem(char *is)
{
unsigned long int rslt = 0;
int x = 0;
if (*is == '+')
is++;
while (is[x] != '\0')
{
if (is[x] >= '0' && is[x] <= '9')
{
rslt *= 10;
rslt += (is[x] - '0');
if (rslt > INT_MAX)
return (-1);
}
else
return (-1);
x++;
}
return (rslt);
}
/**
 * custom_shell_disp_error - A function that displays an error message
 * @in: A structure containing the parameters and the return statements
 * @etype: A string that specifies the ctype of error
 * Return: 0 if there are no issues in the string, -1 on error
 */
void custom_shell_disp_error(unique_info_t *in, char *etype)
{
unique_error_eputs(in->custom_filename);
unique_error_eputs(": ");
custom_shell_error_d(in->custom_error_count, STDERR_FILENO);
unique_error_eputs(": ");
unique_error_eputs(in->custom_arguments[0]);
unique_error_eputs(": ");
unique_error_eputs(etype);
}
/**
 * custom_shell_error_d - A function that prints a decimal
 * (integer) number (base 10)
 * @in: the integer that has been inputed and is expected to be printed
 * @file_d: the file descriptor being written to
 * Return: the exact number of characters that was printed
 */
int custom_shell_error_d(int in, int file_d)
{
int (*custom_gen__putchar)(char) = custom_gen_putchar;
int cnt = 0;
int x;
char sn = (in < 0) ? '-' : 0;
unsigned int a = in < 0 ? -in : in;
if (file_d == STDERR_FILENO)
custom_gen__putchar = unique_error_eputchar;
if (sn)
{
custom_gen__putchar('-');
cnt++;
}
for (x = 1000000000; x > 1; x /= 10)
{
if (a / x)
{
custom_gen__putchar('0' + a / x);
cnt++;
}
a %= x;
}
custom_gen__putchar('0' + a);
cnt++;
return (cnt);
}
/**
 * custom_shell_digit_conv - A function that converts a number to a
 * string in a specified base
 * @n: number being converted
 * @b: The base of the conversion
 * @af: Additional argument flags
 * Return: The string that represents the converted number
 */
char *custom_shell_digit_conv(long int n, int b, int af)
{
static char *array;
static char buffer[50];
char *ptr;
unsigned long a = n;
if (!(af & UNIQUE_CONVERT_UNSIGNED) && n < 0)
{
a = -n;
array = af & UNIQUE_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
}
ptr = &buffer[49];
*ptr = '\0';
do {
*--ptr = array[a % b];
a /= b;
} while (a != 0);
if (n < 0)
*--ptr = '-';
return (ptr);
}
/**
 * custom_shell_rem_usr_com - A function that replaces first
 * instance of '#' with '\0' in a string
 * @sa: Address of string to being modified
 * Return: 0
 */
void custom_shell_rem_usr_com(char *sa)
{
int x;
for (x = 0; sa[x] != '\0'; x++)
if (sa[x] == '#' && (!x || sa[x - 1] == ' '))
{
sa[x] = '\0';
break;
}
}
