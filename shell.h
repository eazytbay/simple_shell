#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

typedef struct ShellVariables
{
char **arguments;
char *command_buffer;
char **environment;
size_t command_count;
char **initial_arguments;
int exit_status;
char **commands;
} vars_t;

typedef struct builtins
{
char *name;
void (*f)(vars_t *);
} builtins_t;

char **duplicate_environment(char **environment);
void free_environment(char **environment);

ssize_t write_string(char *str);
char *duplicate_string(char *str_to_duplicate);
int compare_strings(char *string1, char *string2);
char *concatenate_strings(char *str1, char *str2);
unsigned int string_length(char *str);

char **tokenize_string(char *buffer, char *delimiter);
char **reallocate_memory(char **ptr, size_t *size);
char *custom_strtok(char *str, const char *delim);

void (*find_builtin(vars_t *vars))(vars_t *vars);
void exit_shell(vars_t *vars);
void print_environment(vars_t *vars);
void set_environment_variable(vars_t *vars);
void unset_environment_variable(vars_t *vars);

void add_key_value_pair(vars_t *vars);
char **find_key_in_environment(char **environment, char *key);
char *append_value_to_key(char *key, char *value);
int convert_string_to_integer(char *str);

void search_for_executable_in_path(vars_t *vars);
int execute_from_path(char *command, vars_t *vars);
char *find_executable_path(char **environment);
int execute_from_current_directory(vars_t *vars);
int check_for_directory(char *str);

void print_error_message(vars_t *vars, char *msg);
void write_string_to_stderr(char *str);
char *convert_unsigned_integer_to_string(unsigned int count);

#endif /* _MY_SHELL_H_ */

