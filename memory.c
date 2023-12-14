#include "shell.h"

/**
 * bfree - function to free pointer
 * @ptr: represents address to pointer
 *
 * Return: For success 1, 0 for otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
