/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 02:19:30 by asimoes           #+#    #+#             */
/*   Updated: 2020/05/26 01:25:00 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	size_t					readlen;
	char					*buffer;
	char					*readbuf;
	static char				*rest;
	static unsigned int		restlen;
	char					*endpos;
	unsigned int			line_size;

	#ifdef BUFFER_SIZE
	if (!(buffer = malloc(BUFFER_SIZE)))
		return (-1);
	readbuf = buffer;
	endpos = NULL;
	while ((readlen = read(fd, readbuf, BUFFER_SIZE)) > 0)
	{
		// Realloc and append to the line buffer
		// If we find \n we append until the character before and return
		if ((endpos = ft_strchr(readbuf, '\n')) != NULL)
		{
			line_size = restlen + endpos - readbuf + 1;
			if (!(*line = malloc(sizeof(char) * line_size)))
			{
				free(buffer);
				return (-1);
			}
		}
	}
	if (readlen == -1)
	{
		free(buffer);
		return (-1);
	}
	#endif
}