#include "shell.h"

int check_file(char *full_path);

/**
 * find_prog - This finds a program in the path.
 * @data: A pointer to program's data.
 * Return: 0 on success, otherwise error code is returned.
 */
int find_prog(data_of_program *data)
{
	int i = 0, ret_code = 0;
	char **dirs;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = _strcat(_strdup("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	dirs = tokenize_path(data);/* search in the PATH */

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{/* appends the function_name to path */
		dirs[i] = _strcat(dirs[i], data->tokens[0]);
		ret_code = check_file(dirs[i]);
		if (ret_code == 0 || ret_code == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = _strdup(dirs[i]);
			free_array_of_pointers(dirs);
			return (ret_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(dirs);
	return (ret_code);
}

/**
 * tokenize_path - Tokenize path in the dirs.
 * @data: A pointer to program's data
 * Return: Path array of dirs
 */
char **tokenize_path(data_of_program *data)
{
	int i = 0;
	int count_dirs = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = _strdup(PATH);

	/* find the number of dirs in the PATH */
	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			count_dirs++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * count_dirs);

	/*tokenize and duplicate each token of path*/
	i = 0;
	tokens[i] = _strdup(_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = _strdup(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - checks if a file exist, not a directory and
 * it has excecution permissions.
 * @full_path: A pointer to the full filename.
 * Return: 0 on success, or error code if it exists.
 */
int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exist the file*/
	errno = 127;
	return (127);
}
