/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:22:47 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:51:02 by aboncine         ###   ########.fr       */
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

	start = *i;
	size = 0;
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

char	*ft_strtrim(char *s1, char *set)
{
	char		*newstr;
	size_t		i;
	size_t		last;
	size_t		first;

	i = 0;
	if (ft_strncmp(s1, "\"\"", 2) == 0 || ft_strncmp(s1, "''", 2) == 0)
	{
		if (s1[2] == '\0')
		{
			newstr = malloc(1);
			newstr[0] = '\0';
			return (newstr);
		}
	}
	first = count_c_s(s1, set);
	last = count_c_e(s1, set);
	ft_check_if_trimmable(s1, &first, &last);
	newstr = (char *) malloc(sizeof(char) * (last - first + 1));
	while (first < last)
		newstr[i++] = s1[first++];
	newstr[i] = '\0';
	return (newstr);
}
