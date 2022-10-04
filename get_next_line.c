/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:38 by samartin          #+#    #+#             */
/*   Updated: 2022/10/04 18:57:54 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char	*line;

	line = calloc (1, sizeof (char));
	if (!line)
		return (NULL);
	return (line);
}


#include <fcntl.h>

int main()
{
	int			file;
	int			rtrn_buff;
	char		*str;
	static char *read_buff;

	file = open("textfile.txt", O_RDONLY);
	rtrn_buff = read(file, str, BUFFER_SIZE);
}