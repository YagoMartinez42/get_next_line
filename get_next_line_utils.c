/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:24:47 by samartin          #+#    #+#             */
/*   Updated: 2022/11/06 16:53:27 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;

	pos = 0;
	while ((src[pos] != 0) && ((int)pos < (int)(dstsize - 1)))
	{
		dst[pos] = src[pos];
		pos++;
	}
	if (dstsize > 0)
		dst[pos] = 0;
	while (src[pos] != 0)
		pos++;
	return (pos);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	pos1;
	size_t	pos2;
	size_t	ret;
	size_t	endp;

	pos1 = 0;
	while (dst && dst[pos1])
		pos1++;
	if (pos1 < dstsize)
		ret = pos1;
	else
		ret = dstsize;
	pos2 = -1;
	endp = 0;
	while (src[++pos2])
	{
		if ((pos1 + pos2) < (dstsize - 1) && dstsize > 0)
		{
			dst[pos1 + pos2] = src[pos2];
			endp++;
		}
	}
	if (dstsize != 0 && dstsize >= pos1)
		dst[pos1 + endp] = '\0';
	return (ret + pos2);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	len1;
	unsigned int	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = gnl_len(s1);
	len2 = gnl_len(s2);
	str = malloc(len1 + len2 + 1);
	if (str)
	{
		ft_strlcpy (str, s1, len1 + 1);
		ft_strlcat (str, s2, (len1 + len2 + 1));
	}
	return (str);
}

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
