/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nisim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 11:18:35 by nisim             #+#    #+#             */
/*   Updated: 2026/08/05 17:07:19 by nisim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*st_str;
	char		*buf;
	ssize_t		total_rbyte;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	total_rbyte = 1;
	while (!ft_findnl(st_str) && total_rbyte > 0)
	{
		total_rbyte = read(fd, buf, BUFFER_SIZE);
		if (total_rbyte > 0)
		{
			buf[total_rbyte] = '\0';
			st_str = ft_strjoin_free(st_str, buf);
		}
	}
	free(buf);
	if (total_rbyte < 0 || !st_str || *st_str == '\0')
		return (free(st_str), st_str = NULL, NULL);
	line = ft_fetch_line(st_str);
	return (st_str = ft_strmove(st_str), line);
}
