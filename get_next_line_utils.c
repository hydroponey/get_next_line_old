/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:47:57 by asimoes           #+#    #+#             */
/*   Updated: 2020/05/30 23:52:02 by asimoes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strndup(const char *str, unsigned int n)
{
	char			*copy;
	unsigned int	i;

	if (!(copy = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dst == src)
		return (dst);
	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char		*ft_strnchr(const char *s, int c, int len)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (i < len)
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	return (NULL);
}

void		*ft_realloc(void *ptr, size_t size, size_t ptrsize)
{
	void	*new;

	if (!ptr)
	{
		if (!(new = malloc(size)))
			return (NULL);
	}
	else
	{
		if (!(new = malloc(size)))
			return (NULL);
		ft_memcpy(new, ptr, ptrsize);
		free(ptr);
	}
	return (new);
}

#ifdef BUFFER_SIZE

int			last_line(char **buf, char **line, int *bs, char *readbuf)
{
	if (BUFFER_SIZE == 0)
		return (0);
	if (*buf == NULL)
	{
		*line = (char*)malloc(1);
		*line[0] = '\0';
		free_buffers(readbuf, buf);
		return (0);
	}
	if (process_buffer(buf, line, bs, '\0') == -1)
	{
		free_buffers(readbuf, buf);
		return (-1);
	}
	return (0);
}

#endif
