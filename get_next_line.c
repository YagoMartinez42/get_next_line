/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:13:19 by samartin          #+#    #+#             */
/*   Updated: 2022/10/31 15:13:04 by samartin         ###   ########.fr       */
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

static char	*fill_buffer(int fd, char *buffer)
{
	int	buff_len;

	buff_len = read(fd, (buffer), BUFFER_SIZE);
	if (buff_len < 1)
	{
		free (buffer);
		return (NULL);
	}
	buffer[buff_len] = '\0';
	return (buffer);
}

static char	*buffer_init(int fd, char *buf, char **buf_start)
{
	if (!buf)
	{
		buf = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
		if (!buf)
			return (NULL);
		buf = fill_buffer(fd, buf);
		if (!buf || *(buf) == '\0')
			return (NULL);
		*buf_start = buf;
	}
	else if (*buf == '\0')
	{
		buf = fill_buffer(fd, *buf_start);
		if (!buf || *(buf) == '\0')
			return (NULL);
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf = NULL;
	static char	*buf_start = NULL;

	line = NULL;
	buf = buffer_init(fd, buf, &buf_start);
	if (!buf)
		return (NULL);
	while (!line || (*(line + (gnl_len(line) - 1)) != '\n'))
	{
		buf = append_chnk(&line, buf);
		if (*buf == '\0')
		{
			buf = fill_buffer(fd, buf_start);
			if (!buf || *(buf) == '\0')
				break ;
		}
	}
	return (line);
}
