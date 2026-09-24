/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmainaga <rmainaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:13:31 by rmainaga          #+#    #+#             */
/*   Updated: 2026/09/24 15:35:21 by rmainaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	expand_buffer(char **buf, size_t *cap, size_t len, size_t need)
{
	size_t	new_cap;
	char	*new_buf;

	new_cap = *cap;
	while (new_cap < need)
		new_cap *= 2;
	new_buf = (char *)malloc(new_cap);
	if (!new_buf)
		return (1);
	ft_memcpy(new_buf, *buf, len);
	free(*buf);
	*buf = new_buf;
	*cap = new_cap;
	return (0);
}

static int	read_loop(int fd, char **buf, size_t *len, size_t *cap)
{
	char	chunk[4096];
	ssize_t	rd;

	rd = read(fd, chunk, sizeof(chunk));
	while (rd > 0)
	{
		if (*len + (size_t)rd + 1 > *cap
			&& expand_buffer(buf, cap, *len, *len + (size_t)rd + 1))
			return (1);
		ft_memcpy(*buf + *len, chunk, (size_t)rd);
		*len += (size_t)rd;
		rd = read(fd, chunk, sizeof(chunk));
	}
	if (rd < 0)
		return (1);
	return (0);
}

char	*read_entire_file(const char *path)
{
	int		fd;
	size_t	len;
	size_t	cap;
	char	*buf;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (rt_error("cannot open scene file", -1), NULL);
	len = 0;
	cap = 4096;
	buf = (char *)malloc(cap);
	if (!buf)
		return (close(fd), rt_error("malloc failed", -1), NULL);
	if (read_loop(fd, &buf, &len, &cap))
		return (close(fd), free(buf),
			rt_error("cannot read scene file", -1), NULL);
	close(fd);
	buf[len] = '\0';
	return (buf);
}
