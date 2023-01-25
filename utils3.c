/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:22:47 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/25 14:51:39 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_str4(char const *s, int *i, int *size)
{
	char	*res;
	int		j;

	j = 0;
	res = (char *) malloc(sizeof(char) * (*size + 1));
	if (!res)
		return (NULL);
	while (j < *size)
	{
		res[j++] = s[*i];
		*i += 1;
	}
	res[j] = '\0';
	return (res);
}

char	*create_str3(char const *s, int *i, int *flag, char *c)
{
	int		start;
	int		size;
	int		j;

	start = *i;
	size = 0;
	j = 0;
	while (s[start] != *c && s[start])
	{
		if (s[start] == 34 || s[start] == 39)
		{
			*flag = 1;
			break ;
		}
		size++;
		start++;
	}
	return (create_str4(s, i, &size));
}

static size_t	count_c_s(char const *s1, char const *set)
{
	size_t	i;
	size_t	res;
	size_t	x;

	i = 0;
	res = 0;
	x = 0;
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			res++;
			x = 0;
			i++;
		}
		else
			x++;
	}
	return (res);
}

static size_t	count_c_e(char const *s1, char const *set)
{
	size_t	i;
	size_t	x;
	size_t	res;

	x = 0;
	i = ft_strlen(s1) - 1;
	res = ft_strlen(s1);
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			res--;
			x = 0;
			i--;
		}
		else
			x++;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*newstr;
	size_t		i;
	size_t		last;
	size_t		first;

	i = 0;
	first = count_c_s(s1, set);
	last = count_c_e(s1, set);
	if (s1[first] == '\0')
	{
		first = 0;
		last = 0;
	}
	newstr = (char *) malloc(sizeof(char) * (last - first + 1));
	if (!newstr)
		return (NULL);
	while (first < last)
	{
		newstr[i] = s1[first];
		i++;
		first++;
	}
	newstr[i] = '\0';
	return (newstr);
}
