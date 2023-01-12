/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:28:17 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/12 16:27:04 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
void	create_str(char const *s, char **splitted, char c)
{
	char	quote;
	int		i;
	int		num;
	int		j;
	int		size;
	int		start;
	int		flag;

	i = 0;
	num = 0;
	j = 0;
	size = 0;
	while(s[i] == c && s[i])
		i++;
	while (s[i])
	{
		flag = 0;
		if (s[i] == 34 || s[i] == 39)
			quote = s[i];
		if (s[i] == quote)
		{
			i++;
			/* if (s[i] != quote)
			{ */
				start = i;
				while (s[start] != quote)
				{
					size++;
					start++;
				}
				splitted[num] = (char *) malloc(sizeof(char) * (size + 1));
				if (!splitted[num])
					return ;
				while (j < size)
				{
					splitted[num][j++] = s[i++];
				}
				splitted[num][j] = '\0';
				num++;
				size = 0;
				j = 0;
			//}
		}
		else if (s[i] != c)
		{
			start = i;
			while (s[start] != c && s[start])
			{
				if (s[start] == 34 || s[start] == 39)
				{
					flag = 1;
					break ;
				}
				size++;
				start++;
			}
			splitted[num] = (char *) malloc(sizeof(char) * (size + 1));
			if (!splitted[num])
				return ;
			while (j < size)
			{
				splitted[num][j++] = s[i++];
			}
			splitted[num][j] = '\0';
			num++;
			size = 0;
			j = 0;
		}
		if (flag == 0 && s[i] != '\0')
			i++;
	}
	splitted[num] = 0;
}

int	count_words(char const *s, char c)
{
	int	count;
	int	i;
	char	quote;

	count = 0;
	i = 0;
	if (s[0] != c)
		count++;
	i++;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			quote = s[i];
		if (s[i] == quote)
		{
			i++;
			//if (i == quote)
			//	i++;
			//else
			if (i != quote)
			{
				while(s[i] != quote && s[i])
					i++;
				//i++;
				count++;
			}
		}
		else if ((s[i -1] == c && s[i] != c) || (s[i -1] == quote && s[i] != c))
			count++;
		i++;
	}
	return (count);
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

int main()
{
	char const	*s = "ciao \"ofhjh iooyh fd'ffb' dqdqw\"perche";
	char	**splitted;
	int i = 0;

	splitted = ft_split(s, ' ');
	while(splitted[i])
	{
		printf("%s\n", splitted[i]);
		free(splitted[i]);
		i++;
	}
	free(splitted);
}
