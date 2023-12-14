#include "shell.h"

/**
 * _strlen - defines length of a string
 * @s: input string
 *
 * Return: integer representing length for success
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first input
 * @s2: second input
 *
 * Return: a negative value for s1 < s2,
 * a positive value for s1 > s2 and 0 for s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checksthe beginning of a needle
 * @haystack: input parameter
 * @needle: input parameter
 *
 * Return: address for success or NULL for failure
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - joins two strings
 * @dest: represents the end point
 * @src: represents the starting point
 *
 * Return: pointerfor success
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
