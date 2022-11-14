/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:07:05 by samartin          #+#    #+#             */
/*   Updated: 2022/11/14 12:08:27 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	*gnl_memcpy(void *dst, const void *src, int n)
{
	void	*ret;

	if (dst == NULL || src == NULL)
		return (NULL);
	ret = dst;
	while (n > 0)
	{
		*(unsigned char *)dst = *(unsigned char *)src;
		dst++;
		src++;
		n--;
	}
	return (ret);
}

void	*gnl_mexpand(void *ptr, int size)
{
	char	*ret_ptr;
	int		i;

	ret_ptr = malloc(size * sizeof(char));
	i = 0;
	while (i < size)
	{
		ret_ptr[i] = 0;
		i++;
	}
	if (!ret_ptr)
		return (NULL);
	if (ptr && *(char *)ptr)
	{
		size = gnl_len(ptr) + 1;
		ret_ptr = gnl_memcpy(ret_ptr, ptr, size);
		free (ptr);
	}
	return ((void *)ret_ptr);
}

int	gnl_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strncat(char *dest, char *src, int nb)
{
	int	pos1;
	int	pos2;

	pos1 = 0;
	pos2 = 0;
	while (dest[pos1] != '\0')
		pos1++;
	while (src[pos2] != '\0' && pos2 < nb)
	{
		dest[pos1] = src[pos2];
		pos1++;
		pos2++;
	}
	dest[pos1] = '\0';
	return (dest);
}
