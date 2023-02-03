/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:28:17 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/03 12:35:51 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_str2(char const *s, int *i, char *quote)
{
	int		start;
	int		size;
	char	*res;
	int		j;

	*i += 1;
	start = *i;
	size = 0;
	j = 0;
	while (s[start++] != *quote)
		size++;
	res = (char *) malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	while (j < size)
	{
		res[j++] = s[*i];
		*i += 1;
	}
	res[j] = '\0';
	return (res);
}

void	create_str(char const *s, char **splitted, char c)
{
	char	quote;
	int		i;
	int		num;
	int		flag;

	i = 0;
	num = 0;
	quote = '\0';
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		flag = 0;
		if (s[i] == 34 || s[i] == 39)
			quote = s[i];
		if (s[i] == quote)
			splitted[num++] = create_str2(s, &i, &quote);
		else if (s[i] != c)
			splitted[num++] = create_str3(s, &i, &flag, &c);
		if (flag == 0 && s[i] != '\0')
			i++;
	}
	splitted[num] = 0;
}

int	count_words2(char const *s, int *i, int count, char c)
{
	char	quote;

	quote = '\0';
	while (s[*i])
	{
		if (s[*i] == 34 || s[*i] == 39)
			quote = s[*i];
		if (s[*i] == quote)
		{
			*i = *i + 1;
			if (*i != quote)
			{
				while (s[*i] != quote && s[*i])
					*i = *i + 1;
				count++;
			}
		}
		else if ((s[*i -1] == c && s[*i] != c)
			|| (s[*i -1] == quote && s[*i] != c))
			count++;
		*i = *i + 1;
	}
	return (count);
}

int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	i++;
	return (count_words2(s, &i, count, c));
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	int		num_words;

	num_words = count_words(s, c);
	splitted = (char **) malloc(sizeof(char *) * (num_words + 1));
	if (!splitted)
		return (NULL);
	create_str(s, splitted, c);
	return (splitted);
}
