#include "shell.h"

/**
 * input_buf - stores linked commands together
 * @info: structure containing parameters
 * @buf: location of the buffer.
 * @len: pointer to the variable 'len'.
 *
 * Return: returns number of bytes that were read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If the buffer is empty, populate it. */
	{
		/* Free the memory allocated for info's cmd_buf. */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Eliminate the newline character at the end. */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* Does the presence of a semicolon in *buf indicate a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - retrieves a line without the newline character
 * @info: structure containing parameters.
 *
 * Return: returns number of bytes that were read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* There are remaining commands in the chain buffer. */
	{
		j = i; /* Initialize a new iterator starting from the current position in the buffer. */
		p = buf + i; /* Obtain the pointer for returning. */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Move through until reaching a semicolon or the conclusion. */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Advance beyond the terminated ';' character. */
		if (i >= len) /* Has the buffer's end been reached? */
		{
			i = len = 0; /*  sets the position and length back to their default values */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass bac */
		return (_strlen(p)); /* provides the size of the current command */
	}

	*buf_p = buf; /* If it's not a chain, then return the buffer obtained from _getline(). */
	return (r); /* returns the size of the buffer obtained from _getline() */
}

/**
 * read_buf - etrieves data from a buffer
 * @info: structure holding parameters.
 * @buf: storage area or memory buffer
 * @i: the magnitude or dimension
 *
 * Return: returns result
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - retrieves the following line of
 *            input from the standard input (STDIN)
 * @info: structure containing parameters.
 * @ptr:  location of the pointer to a buffer,
 *          which can be preallocated or NULL.
 * @length: the allocated size of ptr buffer if it's not NULL
 *
 * Return: return a string.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - prevents action of pressing ctrl-C from executing.
 * @sig_num: the number of the signal.
 *
 * Return: return nothing.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
