/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bstrong <bstrong@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 20:42:59 by bstrong           #+#    #+#             */
/*   Updated: 2021/10/27 20:42:59 by bstrong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup_gnl(char *s, char *del)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s) + 1;
	dest = (char *)malloc(size);
	if (!dest || !s || size == 1)
	{
		free (del);
		free(dest);
		return (NULL);
	}
	ft_memcpy(dest, s, size);
	free(del);
	return (dest);
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s2)
		return (s1);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	free(s1);
	return (result);
}

static char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	len_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (len >= len_str)
		len = len_str - start;
	if (start >= len_str || !*s || !len)
		return (ft_strdup_gnl("", NULL));
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	result[len] = 0;
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}

static int	read_data(int fd, char **sym_nl, char **s_left_str)
{
	int		rd;
	char	*buf;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf || fd < 0 || BUFFER_SIZE < 1)
	{
		free(buf);
		return (-1);
	}
	rd = read(fd, buf, BUFFER_SIZE);
	while (rd > 0)
	{
		buf[rd] = 0;
		*s_left_str = ft_strjoin_gnl(*s_left_str, buf);
		*sym_nl = ft_strchr(*s_left_str, '\n');
		if (*sym_nl)
			break ;
		rd = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	return (rd);
}

char	*get_next_line(int fd)
{
	static char	*s_left_str;
	char		*result;
	char		*sym_nl;
	int			rd;

	sym_nl = NULL;
	rd = read_data(fd, &sym_nl, &s_left_str);
	if (rd < 0 || !s_left_str)
		return (NULL);
	else if (rd == 0)
		sym_nl = ft_strchr(s_left_str, '\n');
	if (!sym_nl)
	{
		result = s_left_str;
		s_left_str = NULL;
		return (result);
	}
	result = ft_substr_gnl(s_left_str, 0, sym_nl - s_left_str + 1);
	s_left_str = ft_strdup_gnl(sym_nl + 1, s_left_str);
	return (result);
}
