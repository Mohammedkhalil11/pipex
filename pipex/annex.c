/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   annex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 23:52:56 by mokhalil          #+#    #+#             */
/*   Updated: 2023/02/16 23:33:58 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	i = 0;
	while (s[i + start] && i < len)
		i++;
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (s[i + start] && i < len)
	{
		p[i] = s[i + start];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**free_things(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		strings[i] = NULL;
		i++;
	}
	free(strings);
	strings = NULL;
	return (strings);
}

char	**ft_cp(const char *s, char c, char **string)
{
	int	i;
	int	j;
	int	index;

	j = 0;
	i = 0;
	index = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			while (s[j] && s[j] != c)
				j++;
			string[index++] = ft_substr(s, 0, j);
			if (!string[index - 1])
				return (free_things(string));
			s += j;
		}
	}
	string[index] = NULL;
	return (string);
}

char	**ft_split(char const *s, char c)
{
	char	**string;

	string = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!string)
		return (NULL);
	ft_cp(s, c, string);
	return (string);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*start;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return (0);
	start = p;
	ft_memcpy(p, s1, ft_strlen(s1));
	p += ft_strlen((s1));
	ft_memcpy(p, s2, ft_strlen(s2));
	p += ft_strlen((s2));
	*p = '\0';
	return (start);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*k;

	k = (unsigned char *) src;
	p = (unsigned char *) dest;
	i = 0;
	if (src == dest || !n)
		return (dest);
	while (i < n)
	{
		p[i] = k[i];
		i++;
	}
	return (dest);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	if (count && size > SIZE_MAX / count)
		return (0);
	s = malloc(count * size);
	if (!s)
		return (NULL);
	ft_bzero(s, count * size);
	return ((char *)s);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*k;
	unsigned char	*j;
	size_t			i;

	k = (unsigned char *)s1;
	j = (unsigned char *)s2;
	i = 0;
	while (n > 0 && i < n)
	{
		if (k[i] == '\0' || j[i] == '\0')
			return (k[i] - j[i]);
		if (k[i] == j[i])
		{
			if (i == (n))
				return (0);
		}
		if (k[i] > j[i])
			return (1);
		if (k[i] < j[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)malloc(ft_strlen(s1) + 1);
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
