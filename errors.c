#include "shell.h"

/**
 *_eputs -  displays a provided string
 * @str: the string for output
 *
 * Return:  returns no specific output
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - outputs the character 'c'
 *    to the standard error stream
 * @c: The character for output
 * Return:  Returns 1 if successful.
 *   In case of an error,
 *   -1 is returned,
 *   and errno is adjusted accordingly.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - outputs the character 'c'
 *     to the specified file descriptor
 * @c: The character for printing
 * @fd: The file descriptor for writing
 *
 * Return: Returns 1 upon success.
 *   If there's an error,
 *   -1 is returned,
 *   and errno is adjusted accordingly.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - displays a given string
 * @str: the string for printing
 * @fd: the file descriptor for writing
 *
 * Return: the count of characters placed
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
