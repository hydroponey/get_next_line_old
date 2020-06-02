/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:00:32 by asimoes           #+#    #+#             */
/*   Updated: 2020/06/02 07:44:31 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				free_fd_data(t_fd_data **start)
{
	t_fd_data	*cur;

	while (*start)
	{
		cur = *start;
		*start = cur->next;
		free(cur->buf);
		free(cur);
	}
	return (-1);
}

t_fd_data		*get_fd_data(t_fd_data **start, int fd)
{
	t_fd_data	*new;
	t_fd_data	*cur;
	t_fd_data	*last;

	cur = *start;
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		if (cur->next == NULL)
			last = cur;
		cur = cur->next;
	}
	if (!(new = malloc(sizeof(t_fd_data))))
		return (NULL);
	new->buf = NULL;
	new->eof = 0;
	new->fd = fd;
	new->next = NULL;
	new->size = 0;
	if (*start == NULL)
		*start = new;
	else
		last->next = new;
	return (new);
}

#ifdef BUFFER_SIZE

int				get_line(t_fd_data *d, char **line, t_fd_data **start)
{
	char			*newbuf;
	char			*endl;

	if (d->buf == NULL)
		return (ERR_BUFFER_NULL);
	if ((endl = ft_strnchr(d->buf, '\n', d->size)))
	{
		if (!(*line = ft_strndup(d->buf, (endl - d->buf))))
			return (ERR_MALLOC);
		if (!(newbuf = malloc(d->size - (endl - d->buf) - 1)))
			return (ERR_MALLOC);
		d->size -= (endl - d->buf) + 1;
		ft_memcpy(newbuf, d->buf + (endl - d->buf) + 1, d->size);
		free(d->buf);
		d->buf = newbuf;
		return (1);
	}
	else if (d->eof)
	{
		if (!(*line = ft_strndup(d->buf, d->size)))
			return (ERR_MALLOC);
		return (remove_fd_data(d, start));
	}
	return (ERR_NO_LINE);
}

int				read_loop(t_fd_data *d, char **line, t_fd_data **start)
{
	char	*readbuf;
	int		readlen;
	int		gl_value;

	if (!(readbuf = malloc(BUFFER_SIZE)))
		return (ERR_MALLOC);
	while ((readlen = read(d->fd, readbuf, BUFFER_SIZE)) >= 0)
	{
		if (!(d->buf = ft_realloc(d->buf, d->size + readlen, d->size)))
		{
			free(readbuf);
			return (ERR_MALLOC);
		}
		ft_memcpy(d->buf + d->size, readbuf, readlen);
		d->size += readlen;
		d->eof = (readlen == 0) ? 1 : 0;
		gl_value = get_line(d, line, start);
		if (gl_value != ERR_NO_LINE && gl_value != ERR_BUFFER_NULL)
		{
			free(readbuf);
			return (gl_value);
		}
	}
	free(readbuf);
	return (ERR_READ_FAILURE);
}

int				get_next_line(int fd, char **line)
{
	static t_fd_data	*fd_data;
	t_fd_data			*cur;
	int					gl_value;
	int					retval;

	if (BUFFER_SIZE == 0)
		return (-1);
	if (!(cur = get_fd_data(&fd_data, fd)))
		return (free_fd_data(&fd_data));
	gl_value = get_line(cur, line, &fd_data);
	if (gl_value == ERR_MALLOC)
		return (free_fd_data(&fd_data));
	else if (gl_value != ERR_NO_LINE && gl_value != ERR_BUFFER_NULL)
		return (gl_value);
	retval = read_loop(cur, line, &fd_data);
	if (retval == ERR_READ_FAILURE || retval == ERR_MALLOC)
		return (free_fd_data(&fd_data));
	return (retval);
}

#endif
