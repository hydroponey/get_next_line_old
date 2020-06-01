/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asimoes <asimoes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:47:57 by asimoes           #+#    #+#             */
/*   Updated: 2020/06/01 17:52:42 by asimoes          ###   ########.fr       */
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

int			remove_fd_data(t_fd_data *fd_data)
{
	free(fd_data->buf);
	fd_data->fd = -1;
	fd_data->size = -1;
	fd_data->eof = -1;
	return (0);
}