#ifndef SHELL_H
#define SHELL_H


#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/

#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>

#include <errno.h> /* for errno and perror */
#include <sys/types.h>
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */

/**
 * struct info- struct for the program's data
 *
 */

typedef struct info
{
	int file_descriptor;
	char **tokens;
	char **env;
	char **alias_list;
	char *program_name;
	char *input_line;
	char *command_name;
	int exec_counter;
}data_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */

typedef struct builtins
{
	char *builtin;
	int (*function)(data_of_program *data);
} builtins;

void init_data(data_of_program *data, int arc, char *argv[], char **env);
void infinite(char *prompt, data_of_program *data);
int _getline(data_of_program *data);
int check_logic_ops(char *array_commands[], int i, char array_operators[]);
void infinite(char *prompt, data_of_program *data);

void expand_vars(data_of_program *data);
void expand_alias(data_of_program *data);
int buffer_addition(char *buffer, char *str_to_add);

int exec(data_of_program *data);
int builtins_list(data_of_program *data);
char **tokenize_path(data_of_program *data);
int find_prog(data_of_program *data);

void tokenize(data_of_program *data);
char *_strtok(char *line, char *delim);

int builtin_exit(data_of_program *data);
int builtin_cd(data_of_program *data);
int set_working_directory(data_of_program *data, char *new_dir);
int builtin_help(data_of_program *data);
int builtin_alias(data_of_program *data);



#endif
