#include "shell.h"
/**
 * main - Initialize the program variables.
 * @argc: Number of values received from the cmdline
 * @argv: values received from the cmdline
 * @env: Shell environment
 * Return: 0 on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	data_of_program data_struct = {NULL}, *data = &data_struct;
	char *msg_terminal = "";

	init_data(data, argc, argv, env);
	signal(SIGINT, manag_eof);
if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		msg_terminal = PROMPT;
	}
	errno = 0;
	infinite(msg_terminal, data);
	return (0);
}


/**
 * manag_eof - Display msg_terminal on a newline
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: an option of the prototype.
 */

void manag_eof(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT);
}

/**
 * init_data - Initializes program info into the structure
 * @data: A pointer to data structure
 * @argv: An array of args passed to program for execution.
 * @env: An env passed to the program for execution
 * @argc: The number of values received from the cmdline
 */

void init_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int j = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[j]; j++)
		{
			data->env[j] = _strdup(env[j]);
		}
	}
	data->env[j] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
	{
		data->alias_list[j] = NULL;
	}
}
/**
 * infinite - Prompt loop
 * @msg_terminal: Printed msg_terminal
 * @data: Prompt loop displays
 */

void infinite(char *msg_terminal, data_of_program *data)
{
	int err_code = 0, string_length = 0;

	while (++(data->exec_counter))
	{
		_print(msg_terminal);
		err_code = string_length = _getline(data);
		if (err_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_length >= 1)
		{
			expand_alias(data);
			expand_vars(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to msg_terminal, exec */
				err_code = exec(data);
				if (err_code != 0)
					_print_error(err_code, data);
			}
			free_recurrent_data(data);
		}
	}
}
