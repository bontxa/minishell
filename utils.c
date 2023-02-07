/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:44:01 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/07 11:03:34 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		b;
	char	*newstr;

	i = 0;
	b = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	while (s1[b])
	{
		newstr[i] = s1[b];
		i++;
		b++;
	}
	b = 0;
	while (s2[b])
	{
		newstr[i] = s2[b];
		i++;
		b++;
	}
	newstr[i] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*newstr;

	i = ft_strlen(s);
	newstr = malloc(sizeof(char) * i + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strncpy(char *s, int start, int finish)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (finish - start + 1));
	while (start < finish)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}
