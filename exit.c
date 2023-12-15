#include "shell.h"

/**
 **_strncpy - this duplicates a strng
 *@dest: the target string for the copy operation
 *@src: the originating sequence of characters
 *@n: the number of characters to be replicated
 *Return: returns combined string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - combines two strings, considering a limited number of characters
 *@dest: the initial sequence of characters
 *@src: the second sequence of characters
 *@n: the maximum number of bytes to be utilized
 *Return:  returns the combine string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - finds a character's position within a string
 *@s: the string to be analyzed
 *@c: the character to search for
 *Return: (s) a reference to memory location s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
