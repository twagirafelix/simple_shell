#include "shell.h"

/**
 * builtins_list - search for match and execute the associated builtin func.
 * @data: A struct containing the program's data.
 * Return: Returns the return of the function executed if there is a match,
 * otherwise returns -1.
 **/
int builtins_list(data_of_program *data)
{
	int opt_iterators;
	builtins customs[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (opt_iterators = 0; customs[opt_iterators].builtin != NULL; opt_iterators++)
	{
/*if there is a match between the given command and a builtin,*/
		if (_strcmp(customs[opt_iterators].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (customs[opt_iterators].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
