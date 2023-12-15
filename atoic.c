#include "shell.h"

/**
 * interactive - yields true if the shell is in interactive mode
 * @info: structure defining an address
 *
 * Return: returns 1 for interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - verifies whether the character is a delimiter
 * @c: the character to examine
 * @delim: the separator string
 * Return: returns 1 for true,
 * 0 for false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - verifies if the character is an alphabet
 *@c: The character to be entered
 *Return: returns 1 if 'c' is a letter,0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - changes a string into an integer
 *@s: the string to be transformed
 *Return: return 0 if there are no numbers in the string,
 * the converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
