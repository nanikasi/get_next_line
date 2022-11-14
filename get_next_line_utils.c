/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_tmp.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nanakani <nanakani@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:46:54 by nanakani          #+#    #+#             */
/*   Updated: 2022/11/09 16:46:54 by nanakani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*string;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	while (i < s1_len)
	{
		string[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		string[s1_len + i] = s2[i];
		i++;
	}
	string[s1_len + i] = '\0';
	return (string);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*ch_dst;
	size_t	src_len;
	size_t	i;

	ch_dst = dst;
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize - 1 && i < src_len)
	{
		ch_dst[i] = src[i];
		i++;
	}
	ch_dst[i] = '\0';
	return (src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (i < n)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		dest[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
