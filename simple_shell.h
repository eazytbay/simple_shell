#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
/* Read and write buffer sizes */
#define UNIQUE_READ_BUFFER_SIZE 1024
#define UNIQUE_WRITE_BUFFER_SIZE 1024
#define UNIQUE_BUFFER_FLUSH -1

/* Command chaining constants */
#define UNIQUE_CMD_NORMAL 0
#define UNIQUE_CMD_OR 1
#define UNIQUE_CMD_AND 2
#define UNIQUE_CMD_CHAIN 3

/* Character conversion constants */
#define UNIQUE_CONVERT_LOWERCASE 1
#define UNIQUE_CONVERT_UNSIGNED 2

/* Indicator for using system getline() */
#define UNIQUE_USE_GETLINE 0
#define UNIQUE_USE_STRTOK 0

#define UNIQUE_HISTORY_FILE ".simple_shell"
#define UNIQUE_HISTORY_MAX 4096

extern char **unique_environment;

/**
 * struct unique_list -  A singly linked list
 * @dig: the digit field
 * @str: the string
 * @next: next node pointer
 */
typedef struct unique_list
{
int dig;
char *str;
struct unique_liststr *next;
}
unique_list_t;

/**
 * struct custom_shell_info - encapsulates synthetic arguments for function
 * invocation,ensuring consistent prototypes for function pointer structures
 * @custom_argument: a string derived from the 'getline' function,
 * containing input arguments
 * @custom_arguments: an array of strings created from 'custom_argument'
 * @custom_command_path: a string representing the path to the
 * current command
 * @custom_argument_count: the count of arguments
 * @custom_error_count: counts the errors
 * @custom_line_count_flag: a flag to indicate counting this input line
 * @custom_filename: the program's filename
 * @custom_local_env: a linked list that stores a local copy of the
 * 'environ' environment variables
 * @custom_modified_history: The node that keeps the history
 * @custom_modified_environment: a customized and modified copy of the
 * 'environ' variables from the 'LL env'
 * @custom_alias_node: the alias node
 * @custom_environment_changes: flag indicating if 'environ' has been altered
 * @custom_execution_status: the return status of the last executed command
 * @custom_command_buffer: a pointer to the 'command_buffer'; set when
 * chaining commands
 * @custom_command_buffer_type: command type, such as 'CMD_type ||, &&, ;'
 * @custom_read_file_descriptor: the file descriptor from which to
 * read line input
 * @custom_history_line_count: the count of history line numbers
 */

typedef struct unique_info_t
{
char *custom_argument;
char **custom_arguments;
char *custom_command_path;
int custom_argument_count;
unsigned int custom_error_count;
int miscal_dig;
int custom_line_count_flag;
char *custom_filename;
unique_list_t *custom_local_env;
unique_list_t *custom_modified_history;
unique_list_t *custom_alias_node;
char **custom_modified_environment;
int custom_environment_changes;
int custom_execution_status;

char **custom_command_buffer;
int custom_command_buffer_type;
int custom_read_file_descriptor;
int custom_history_line_count;
}
unique_info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
 * struct unique_builtin - a string that's builtin and all
 * other functios that are related
 * @knd: custom builtin command flag
 * @funt: custom function
 */
typedef struct unique_builtin
{
char *knd;
int (*func)(unique_info_t *);
} unique_builtin_table;

/* my custom Function prototypes */

int unique_terminal(unique_info_t *, char **);
int unique_shell_builtin(unique_info_t *);
void unique_shell_find_cmd(unique_info_t *);
void unique_shell_fork_cmd(unique_info_t *);

/* My custom shell Parser functions */
int unique_shell_cmd(unique_info_t *, char *);
char *unique_shell_char_dup(char *, int, int);
char *unique_shell_path_loc(unique_info_t *, char *, char *);

/* My custom shell Loop functions */
int unique_shell_loop(char **);

/* My custom shell Error functions */
void unique_error_eputs(char *);
int unique_error_eputchar(char);
int unique_error_putfd(char c, int fd);
int unique_error_putsfd(char *str, int fd);

/* My custom gen String functions */
int custom_gen_strlen(char *);
int custom_gen_strcmp(char *, char *);
char *custom_gen_starts_with(const char *, const char *);
char *custom_gen_strcat(char *, char *);

/* My custom shell String functions */
char *custom_gen_strcpy(char *, char *);
char *custom_gen_strdup(const char *);
void custom_gen_puts(char *);
int custom_gen_putchar(char);

/* My uniquely gen Exit functions */
char *custom_gen_strncpy(char *, char *, int);
char *custom_gen_strncat(char *, char *, int);
char *custom_gen_strchr(char *, char);

/* My custom shell Tokenizers*/
char **custom_gen_strtow(char *, char *);
char **custom_gen_sstrtow(char *, char);

/* My custom shell mem Realloc */
char *custom_shell_memset(char *, char, unsigned int);
void custom_shell_ffree(char **);
void *custom_shell_realloc(void *, unsigned int, unsigned int);

/* My custom shell mem */
int custom_shell_mfree(void **);

/* My custom string converter */
int custom_shell_gen_interactive(unique_info_t *);
int unique_delim(char, char *);
int custom_gen_shell_alpha(int);
int custom_gen_shell_atoi(char *);

/* My custom shell Error handlers */
int custom_shell_errorem(char *);
void custom_shell_disp_error(unique_info_t *, char *);
int custom_shell_error_d(int, int);
char *custom_shell_digit_conv(long int, int, int);
void custom_shell_rem_usr_com(char *);

/* My custom shell Built-in functions */
int eazy_exit(unique_info_t *);
int eazy_cd(unique_info_t *);
int eazy_help(unique_info_t *);

/* My custom shell Built-in functions cont */
int eazy_history(unique_info_t *);
int eazy_alias(unique_info_t *);

/* My custom shell Getline functions */
ssize_t custom_read_input(unique_info_t *);
int custom_gen_getline(unique_info_t *, char **, size_t *);
void custom_gen_sign(int);

/* My custom shell Info functions */
void custom_clr_inf(unique_info_t *);
void custom_shell_info_set(unique_info_t *, char **);
void custom_shell_info_free(unique_info_t *, int);

/* My custom shell Env functions */
char *unique_gen_getenv(unique_info_t *, const char *);
int custom_eazy_env(unique_info_t *);
int custom_eazy_setenv(unique_info_t *);
int custom_eazy_remenv(unique_info_t *);
int custom_eazy_pop_env(unique_info_t *);

/* My custom shell Env */
char **custom_fetch_env(unique_info_t *);
int unique_remenv(unique_info_t *, char *);
int uniquely_gen_setenv(unique_info_t *, char *, char *);

/* Eazy custom shell History */
char *custom_fetch_hist(unique_info_t *info);
int custom_show_hist(unique_info_t *info);
int custom_read_history(unique_info_t *info);
int custom_create_history_list(unique_info_t *info, char *buf, int linecount);
int uniquely_reass_num(unique_info_t *info);

/* My custom shell ls functions */
unique_list_t *unique_inc_node(unique_list_t **, const char *, int);
unique_list_t *unique_inc_node_fin(unique_list_t **, const char *, int);
size_t custom_disp_ls_beg(const unique_list_t *);
int custom_rem_node(unique_list_t **, unsigned int);
void custom_rel_lst(unique_list_t **);

/* Eazy custom shell list */
size_t custom_lst_len(const unique_list_t *);
char **custom_str_lst(unique_list_t *);
size_t custom_disp_lst(const unique_list_t *);
unique_list_t *custom_beg_node(unique_list_t *, char *, char);
ssize_t custom_fetch_node(unique_list_t *, unique_list_t *);

/* My shell custom Variables */
int custom_for_chain(unique_info_t *, char *, size_t *);
void custom_ex_chain(unique_info_t *, char *, size_t *, size_t, size_t);
int custom_sub_alias(unique_info_t *);
int custom_sub_vabs(unique_info_t *);
int custom_sub_str(char **, char *);

#endif

