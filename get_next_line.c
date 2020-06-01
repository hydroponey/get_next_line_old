/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:00:32 by asimoes           #+#    #+#             */
/*   Updated: 2020/06/01 18:19:58 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd_data		*get_fd_data(t_fd_data **start, int fd)
{
	t_fd_data	*cur;

	cur = *start;
	if (cur == NULL)
		return (NULL);
	while (cur)
	{
		if (cur->fd == fd)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_fd_data		*add_fd_data(t_fd_data **start, int fd)
{
	t_fd_data	*new;
	t_fd_data	*copy;

	if (!(new = malloc(sizeof(t_fd_data))))
		return (NULL);
	new->buf = NULL;
	new->eof = 0;
	new->fd = fd;
	new->next = NULL;
	new->size = 0;
	if (*start == NULL)
	{
		*start = new;
	}
	else
	{
		copy = *start;
		while (copy->next != NULL)
			copy = copy->next;
		copy->next = new;
	}
	return (new);
}

#ifdef BUFFER_SIZE

int				get_line(t_fd_data *d, char **line)
{
	char			*newbuf;
	char			*endl;

	if (d->buf == NULL)
		return (-2);
	if ((endl = ft_strnchr(d->buf, '\n', d->size)))
	{
		if (!(*line = ft_strndup(d->buf, (endl - d->buf))))
			return (-1);
		if (!(newbuf = malloc(d->size - (endl - d->buf) - 1)))
			return (-1);
		d->size -= (endl - d->buf) + 1;
		ft_memcpy(newbuf, d->buf + (endl - d->buf) + 1, d->size);
		free(d->buf);
		d->buf = newbuf;
		return (1);
	}
	else if (d->eof)
	{
		if (!(*line = ft_strndup(d->buf, d->size)))
			return (-1);
		return (remove_fd_data(d));
	}
	return (-2);
}

int				read_loop(t_fd_data *d, char **line)
{
	char	*readbuf;
	int		readlen;
	int		gl_value;

	if (!(readbuf = malloc(BUFFER_SIZE)))
		return (-1);
	while ((readlen = read(d->fd, readbuf, BUFFER_SIZE)) >= 0)
	{
		d->eof = (readlen == 0) ? 1 : 0;
		gl_value = get_line(d, line);
		if (gl_value != -2)
			return (gl_value);
		if (!(d->buf = ft_realloc(d->buf, d->size + readlen, d->size)))
			return (-1);
		ft_memcpy(d->buf + d->size, readbuf, readlen);
		d->size += readlen;
	}
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	static t_fd_data	*fd_data;
	t_fd_data			*cur;
	int					gl_value;
	int					retval;

	if (!(cur = get_fd_data(&fd_data, fd)))
	{
		if (!(cur = add_fd_data(&fd_data, fd)))
			return (-1);
	}
	gl_value = get_line(cur, line);
	if (gl_value != -2)
		return (gl_value);
	if ((retval = read_loop(cur, line)) == -1)
		return (-1);
	return (retval);
}

#endif
