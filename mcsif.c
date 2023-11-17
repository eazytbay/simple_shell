#include "simple_shell.h"
/**
 * custom_shell_clr_inf - A function that Clears and
 * initializes the info_t struct.
 * @ad: The Address of the info_t struct to be initialized.
 */
void custom_shell_clr_inf(unique_info_t *ad)
{
ad->custom_argument = NULL;
ad->custom_arguments = NULL;
ad->custom_command_path = NULL;
ad->custom_argument_count = 0;
}
/**
 * custom_shell_info_set - Sets up the info_t struct with provided arguments.
 * @ad: Address of the info_t struct to be populated.
 * @agv: vector of the argument.
 */
void custom_shell_info_set(unique_info_t *ad, char **agv)
{
int x;
ad->custom_filename = agv[0];
if (ad->custom_argument)
{
ad->custom_arguments = custom_gen_strtow(ad->custom_argument, " \t");
if (!ad->custom_arguments)
{
ad->custom_arguments = malloc(sizeof(char *) * 2);
if (ad->custom_arguments)
{
ad->custom_arguments[0] = custom_gen_strdup(ad->custom_argument);
ad->custom_arguments[1] = NULL;
}
}
x = 0;
while (ad->custom_arguments && ad->custom_arguments[x])
{
x++;
}
ad->custom_argument_count = x;
custom_sub_alias(ad);
custom_sub_vabs(ad);
}
}
/**
 * custom_shell_info_free - A function that Frees allocated memory
 * in the info_t struct.
 * @ad: Address of the info_t struct to be released.
 * @ev: remains true for freeing every fields.
 */
void custom_shell_info_free(unique_info_t *ad, int ev)
{
custom_shell_ffree(ad->custom_arguments);
ad->custom_arguments = NULL;
ad->custom_command_path = NULL;
if (ev)
{
if (!ad->custom_command_buffer)
free(ad->custom_argument);
if (ad->custom_local_env)
custom_rel_lst(&(ad->custom_local_env));
if (ad->custom_modified_history)
custom_rel_lst(&(ad->custom_modified_history));
if (ad->custom_alias_node)
custom_rel_lst(&(ad->custom_alias_node));
custom_shell_ffree(ad->custom_modified_environment);
ad->custom_modified_environment = NULL;
custom_shell_mfree((void **)ad->custom_command_buffer);
if (ad->custom_read_file_descriptor > 2)
close(ad->custom_read_file_descriptor);
custom_gen_putchar(UNIQUE_BUFFER_FLUSH);
}
}
