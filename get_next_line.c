/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 02:19:30 by asimoes           #+#    #+#             */
/*   Updated: 2020/05/27 10:52:10 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				process_buffer(char **buffer, char **line, int *bufsize)
{
	void			*newbuf;
	char			*endl;
	unsigned int	len;

	if (*buffer != NULL && (endl = ft_strnchr(*buffer, '\n', *bufsize)) != NULL)
	{
		len = endl - (char*)*buffer;
		if (!(*line = ft_strndup(*buffer, len)))
		{
			free(*buffer);
			return (-1);
		}
		if (!(newbuf = malloc(*bufsize - len - 1)))
			return (-1);
		*bufsize -= len + 1;
		ft_memcpy(newbuf, *buffer + len + 1, *bufsize);
		free(*buffer);
		*buffer = newbuf;
		return (1);
	}
	return (0);
}

int				free_buffers(char *readbuf, char **buf)
{
	free(readbuf);
	free(*buf);
	return (-1);
}

int				read_loop(int fd, char **line, char **buf, int *bs)
{
	ssize_t		readlen;
	int			retval;
	char		*readbuf;

	if (!(readbuf = malloc(BUFFER_SIZE)))
		return (free_buffers(readbuf, buf));
	while ((readlen = read(fd, readbuf, BUFFER_SIZE)) > 0)
	{
		if (!(*buf = ft_realloc(*buf, *bs + readlen, *bs)))
			return (free_buffers(readbuf, buf));
		ft_memcpy(*buf + *bs, readbuf, readlen);
		*bs += readlen;
		if ((retval = process_buffer(buf, line, bs)) == 1)
			return (1);
		else if (retval == -1)
			return (free_buffers(readbuf, buf));
	}
	if (readlen == -1)
		return (free_buffers(readbuf, buf));
	return (0);
}

#ifdef BUFFER_SIZE

int				get_next_line_r(int fd, char **line, char **buf, int *bs)
{
	int			retval;

	if ((retval = process_buffer(buf, line, bs)) == 1)
		return (1);
	else if (retval == -1)
		return (-1);
	return (read_loop(fd, line, buf, bs));
}

#endif

int				get_next_line(int fd, char **line)
{
	static char		*buffer = NULL;
	static int		bufsize = 0;

	return (get_next_line_r(fd, line, &buffer, &bufsize));
}
