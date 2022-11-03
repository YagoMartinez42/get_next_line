/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:19 by samartin          #+#    #+#             */
/*   Updated: 2022/11/03 12:45:17 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_chnk(char **line, char *buffer)
{
	int	i;
	int	line_len;

	i = 0;
	line_len = 0;
	if (*buffer == 0)
		buffer++;
	if (*line)
		line_len = gnl_len(*line);
	while (*(buffer + i) && *(buffer + i) != '\n')
		i++;
	if (*(buffer + i) == '\n')
		i++;
	if (i == 0)
		return (NULL);
	*line = (char *)gnl_mexpand(*line, line_len + i + 1);
	*line = gnl_strncat(*line, (buffer), i);
	buffer += i;
	return (buffer);
}

static char	*fill_buffer(int fd, char *buf, char *buf_start)
{
	int	buff_len;

	if (*buf == '\0')
	{
		buf = buf_start;
		buff_len = read(fd, (buf), BUFFER_SIZE);
		if (buff_len < 1)
		{
			free (buf);
			return (NULL);
		}
		buf[buff_len] = '\0';
	}
	return (buf);
}
/*
static char	*buffer_init(int fd, char *buf, char **buf_start)
{

		buf = fill_buffer(fd, buf);
		if (!buf || *(buf) == '\0')
			return (NULL);
	}
	return (buf);
}*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf = NULL;
	static char	*buf_start = NULL;

	if (!buf)
	{
		buf = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
		if (!buf)
			return (NULL);
		*buf = '\0';
		buf_start = buf;
	}
	line = NULL;
	//buf = buffer_init(fd, buf, &buf_start);
	//if (!buf)
	//	return (NULL);
	while (!line || (line[gnl_len(line) - 1] != '\n'))
	{
		buf = fill_buffer(fd, buf, buf_start);
		if (!buf || *(buf) == '\0')
			break ;
		buf = append_chnk(&line, buf);
	}
	return (line);
}
