#include "shell.h"

/**
* _getline - Take one line from the input prompt.
* @data: program's data struct
*
* Return: read count bytes.
*/
int _getline(data_of_program *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commands_array[10] = {NULL};
	static char operators_array[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	/* check if no more commands exist in the array */
	/* and checks for logical operators */
	if (!commands_array[0] || (operators_array[0] == '&' && errno != 0) ||
		(operators_array[0] == '|' && errno == 0))
	{
		/*free the memory allocated in the array if, indeed, it exists */
		for (i = 0; commands_array[i]; i++)
		{
			free(commands_array[i]);
			commands_array[i] = NULL;
		}

		/* read from the file descriptor into to the buffer */
		bytes_read = read(data->file_descriptor, &buff, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		/* this split lines for \n or ; */
		i = 0;
		do {
			commands_array[i] = _strdup(_strtok(i ? NULL : buff, "\n;"));
			/*checks and split for && and || operators*/
			i = check_logic_ops(commands_array, i, operators_array);
		} while (commands_array[i++]);
	}

	/*obtains the next command (command 0) and remove it from the array*/
	data->input_line = commands_array[0];
	for (i = 0; commands_array[i]; i++)
	{
		commands_array[i] = commands_array[i + 1];
		operators_array[i] = operators_array[i + 1];
	}

	return (_strlen(data->input_line));
}


/**
* check_logic_ops - it checks for and then split && and || operators
* @commands_array: an array of the cmds.
* @i: Index to be checked
* @operators_array: an array of the logical operators for each prev cmd
*
* Return: Index of the last cmd
*/
int check_logic_ops(char *commands_array[], int i, char operators_array[])
{
	char *temp = NULL;
	int j;

	/* checks for the & in the command line*/
	for (j = 0; commands_array[i] != NULL  && commands_array[i][j]; j++)
	{
		if (commands_array[i][j] == '&' && commands_array[i][j + 1] == '&')
		{
			/* split the line when && was found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = _strdup(commands_array[i]);
			commands_array[i + 1] = _strdup(temp + j + 2);
			i++;
			operators_array[i] = '&';
			free(temp);
			j = 0;
		}
		if (commands_array[i][j] == '|' && commands_array[i][j + 1] == '|')
		{
			/* split the line when || was found */
			temp = commands_array[i];
			commands_array[i][j] = '\0';
			commands_array[i] = _strdup(commands_array[i]);
			commands_array[i + 1] = _strdup(temp + j + 2);
			i++;
			operators_array[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
