#include "shell.h"

/**
 * long_to_string - This converts number to string.
 * @number: A number to be converted.
 * @string: A buffer to store the number as string.
 * @base: A base to convert the number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int index = 0, inNegative = 0;
	long reminder = number;
	char letters[] = {"0123456789abcdef"};

	if (reminder == 0)
		string[index++] = '0';

	if (string[0] == '-')
		inNegative = 1;

	while (reminder)
	{
		if (reminder < 0)
			string[index++] = letters[-(reminder % base)];
		else
			string[index++] = letters[reminder % base];
		reminder /= base;
	}
	if (inNegative)
		string[index++] = '-';

	string[index] = '\0';
	str_reverse(string);
}


/**
 * _atoi - converts string to an int.
 *
 * @s: A pointer to original string.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int number = 0;
	/*1- analisys sign*/
	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			sign *= -1;
		if (*s == '+')
			sign *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * sign);
}

/**
 * count_characters - This counts the coincidences of chars in string.
 *
 * @string: A pointer to original string.
 * @character: the string with chars to be counted.
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int i = 0, counter = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			counter++;
	}
	return (counter);
}
