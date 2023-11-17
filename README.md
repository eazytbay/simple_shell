Customized Simple Shell Project
Overview
This project implements a customized simple shell, providing a command-line interface for users to interact with the system. The shell supports various features, including environment management, command history, and list operations.

Features and Prototypes
Custom Shell Info Functions
custom_clr_inf: Clears and initializes a custom shell info structure.
custom_shell_info_set: Sets up the custom shell info structure with the provided arguments.
custom_shell_info_free: Frees resources associated with the custom shell info structure.
Custom Shell Env Functions
unique_gen_getenv: Gets the value of a specific environment variable.
custom_eazy_env: Prints the current environment.
custom_eazy_setenv: Initializes a new environment variable or modifies an existing one.
custom_eazy_remenv: Removes an environment variable.
custom_eazy_pop_env: Populates the environment linked list.
Custom Shell Env
custom_fetch_env: Returns the string array copy of the current environment.
unique_remenv: Removes an environment variable.
uniquely_gen_setenv: Initializes a new environment variable or modifies an existing one.
Eazy Custom Shell History
custom_fetch_hist: Fetches the command history.
custom_show_hist: Displays the command history.
custom_read_history: Reads the command history.
custom_create_history_list: Creates a history list.
uniquely_reass_num: Reassigns history numbers.
Custom Shell ls Functions
unique_inc_node: Adds a node to the start of the list.
unique_inc_node_fin: Adds a node to the end of the list.
custom_disp_ls_beg: Prints only the str element of a list_t linked list.
custom_rem_node: Deletes a node at a given index.
custom_rel_lst: Frees all nodes of a list.
Eazy Custom Shell List
custom_lst_len: Determines the length of a linked list.
custom_str_lst: Returns an array of strings from a list.
custom_disp_lst: Prints all elements of a list_t linked list.
custom_beg_node: Adds a node to the beginning of a list.
custom_fetch_node: Gets the index of a node.
My Shell Custom Variables
custom_for_chain: Checks if the current character in the buffer is a chain delimiter.
custom_ex_chain: Checks if we should continue chaining based on the last status.
custom_sub_alias: Replaces aliases in the tokenized string.
custom_sub_vabs: Replaces variables in the tokenized string.
custom_sub_str: Replaces a string.
system calls used
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
Usage
Compilation:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh







