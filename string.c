#include "shell.h"

/**
 * _strlen - String length.
 * @string: A pointer to string.
 * Return: length of string.
 */
int _strlen(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * _strdup - Duplicates a string
 * @string: String to be duplicated
 * Return: a pointer to the array
 */
char *_strdup(char *string)
{
	char *res;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = _strlen(string) + 1;

	res = malloc(sizeof(char) * length);

	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		res[i] = string[i];
	}

	return (res);
}

/**
 * _strcmp - Compare two strings
 * @string1: String 2
 * @string2: String 1
 * @number: The number of characters to be compared, 0 if infinite
 * Return: 1 if equalates ,0 if differs
 */
int _strcmp(char *string1, char *string2, int number)
{
	int counter;

	if (string1 == NULL && string2 == NULL)
		return (1);

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (_strlen(string1) != _strlen(string2))
			return (0);
		for (counter = 0; string1[counter]; counter++)
		{
			if (string1[counter] != string2[counter])
				return (0);
		}
		return (1);
	}
	else /* if there is a number of chars to be compared */
	{
		for (counter = 0; counter < number ; counter++)
		{
			if (string1[counter] != string2[counter])
			return (0);
		}
		return (1);
	}
}

/**
 * _strcat - concatenates 2 strings.
 * @string1: String 1
 * @string2: String 2
 *
 * Return: A pointer to the array
 */
char *_strcat(char *string1, char *string2)
{
	char *res;
	int length1 = 0, length2 = 0;

	if (string1 == NULL)
		string1 = "";
	length1 = _strlen(string1);

	if (string2 == NULL)
		string2 = "";
	length2 = _strlen(string2);

	res = malloc(sizeof(char) * (length1 + length2 + 1));
	if (res == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of string1 */
	for (length1 = 0; string1[length1] != '\0'; length1++)
		res[length1] = string1[length1];
	free(string1);

	/* copy of string2 */
	for (length2 = 0; string2[length2] != '\0'; length2++)
	{
		res[length1] = string2[length2];
		length1++;
	}

	res[length1] = '\0';
	return (res);
}


/**
 * str_reverse - reverses a string.
 *
 * @string: A pointer to string.
 * Return: void.
 */
void str_reverse(char *string)
{

	int i = 0, length = _strlen(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
