#include "simple_shell.h"

/**
 * custom_for_chain - A function that checks the
 * buffer to ascertain if the current
 * character is a chain dlimiter
 * @st: structure containing parameters
 * @ch_buf: buffer's character
 * @ad: Present position of the address in the buf
 * Return: 1 provided the chain a delimiter and 0 if not
 */
int custom_for_chain(unique_info_t *st, char *ch_buf, size_t *ad)
{
size_t y = *ad;
while (ch_buf[y] == '|' && ch_buf[y + 1] == '|')
{
ch_buf[y] = 0;
y++;
st->custom_command_buffer_type = UNIQUE_CMD_OR;
}
while (ch_buf[y] == '&' && ch_buf[y + 1] == '&')
{
ch_buf[y] = 0;
y++;
st->custom_command_buffer_type = UNIQUE_CMD_AND;
}
while (ch_buf[y] == ';')
{
ch_buf[y] = 0;
st->custom_command_buffer_type = UNIQUE_CMD_CHAIN;
}
*ad = y;
return (1);
}
/**
 * custom_ex_chain - A function that confirms if chaining should continue
 * by checking the last status
 * @st: structure containing parameters
 * @ch_buf: character buffer
 * @add: address of the current position in buf
 * @beg: starting position in buf
 * @l: length of buf
 * Return: Void
 */
void check_chain(unique_info_t *st, char *ch_buf, size_t *add,
size_t beg, size_t l)
{
size_t y = *add;
if (st->custom_command_buffer_type == UNIQUE_CMD_AND)
{
if (st->custom_execution_status)
{
ch_buf[beg] = 0;
y = l;
}
}
if (st->custom_command_buffer_type == UNIQUE_CMD_OR)
{
if (!st->custom_execution_status)
{
ch_buf[beg] = 0;
y = l;
}
}
*add = y;
}
/**
 * custom_sub_alias - A function that substitute aliases in a string
 * that has been tokenized
 * @st:  The structure that contains relevant parameters
 * Return: 1 if susbstituted successfully and 0 if not
 */
int custom_sub_alias(unique_info_t *st)
{
int x;
unique_list_t *n;
char *a;
x = 0;
while (x < 10)
{
n = custom_beg_node(st->custom_alias_node, st->custom_arguments[0], '=');
if (!n)
return (0);
free(st->custom_arguments[0]);
a = custom_gen_strchr(n->str, '=');
if (!a)
return (0);
a = custom_gen_strdup(a + 1);
if (!a)
return (0);
st->custom_arguments[0] = a;
x++;
}
return (1);
}
/**
 * custom_sub_vabs - A function that substitutes variables in a
 * string that's tokenized
 * @st: The structure that contains the relevant parameters
 * Return: 1 if substituted successfully and 0 if not
 */
int custom_sub_vabs(unique_info_t *st)
{
int x = 0;
unique_list_t *n;
while (st->custom_arguments[x])
{
if (st->custom_arguments[x][0] != '$' || !st->custom_arguments[x][1])
continue;
if (!custom_gen_strcmp(st->custom_arguments[x], "$?"))
{
custom_sub_str(&(st->custom_arguments[x]),
custom_gen_strdup(custom_shell_digit_conv
(st->custom_execution_status, 10, 0)));
continue;
}
if (!custom_gen_strcmp(st->custom_arguments[x], "$$"))
{
custom_sub_str(&(st->custom_arguments[x]),
custom_gen_strdup(custom_shell_digit_conv(getpid(), 10, 0)));
continue;
}
n = custom_beg_node(st->custom_local_env, &st->custom_arguments[x][1], '=');
if (n)
{
custom_sub_str(&(st->custom_arguments[x]),
custom_gen_strdup(custom_gen_strchr(n->str, '=') + 1));
continue;
}
custom_sub_str(&st->custom_arguments[x], custom_gen_strdup(""));
x++;
}
return (0);
}
/**
 * custom_sub_str - A function that substitutes a string
 * @form: The former string's address
 * @pres: The present string
 * Return: 1 if successfully substitued, 0 if not
 */
int custom_sub_str(char **form, char *pres)
{
free(*form);
*form = pres;
return (1);
}
