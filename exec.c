#include "shell.h"

/**
 * exec - Execute a command.
 * @data: A pointer to the program's data.
 * Return: 0 on success, otherwise -1.
 */

int exec(data_of_program *data)
{
	int return_value = 0, status;
	pid_t pid;

	/* check for program in built ins */
	return_value = builtins_list(data);
	if (return_value != -1)/* if program was found in built ins */
		return (return_value);

	/* check for program file system */
	return_value = find_prog(data);
	if (return_value)
	{/* if program not found */
		return (return_value);
	}
	else
	{/* if program was found */
		pid = fork(); /* create a child process */
		if (pid == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{/* I am the child process, I exec the program*/
			return_value = execve(data->tokens[0], data->tokens, data->env);
			if (return_value == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
