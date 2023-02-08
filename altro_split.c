/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   altro_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 19:17:08 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/08 19:17:09 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_split_flags(char c, int *flagvirgo, int *flagapici)
{
	if (c == 34)
	{
		if (*flagvirgo == 0)
			*flagvirgo = 1;
		else
			*flagvirgo = 0;
	}
	if (c == 39)
	{
		if (*flagapici == 0)
			*flagapici = 1;
		else
			*flagapici = 0;
	}
}

int	ft_how_many_words(char *s)
{
	int	i;
	int	flagapici;
	int	flagvirgo;
	int	count;

	i = 0;
	flagapici = 0;
	flagvirgo = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && (i == 0 || (s[i - 1] == ' '
					&& flagapici == 0 && flagvirgo == 0)))
			count++;
		if (s[i] == 34 || s[i] == 39)
			ft_change_split_flags(s[i], &flagvirgo, &flagapici);
		i++;
	}
	return (count);
}

void	ft_crea_parola_helper(char *s, int *i)
{
	int		flagapici;
	int		flagvirgo;

	flagapici = 0;
	flagvirgo = 0;
	while (s[*i])
	{
		if (s[*i] == ' ' && flagapici == 0 && flagvirgo == 0)
		{
			*i = *i - 1;
			break ;
		}
		if (s[*i] == 34 || s[*i] == 39)
			ft_change_split_flags(s[*i], &flagvirgo, &flagapici);
		*i = *i + 1;
	}
}

char	*ft_crea_parola(char *s, int i)
{
	int		b;
	char	*res;
	int		c;

	b = i;
	c = 0;
	ft_crea_parola_helper(s, &i);
	res = malloc(sizeof(char) * (i - b + 2));
	while (b <= i)
		res[c++] = s[b++];
	res[c] = 0;
	return (res);
}

char	**ft_altro_split(char *s)
{
	char	**res;
	int		i;
	int		b;
	int		flagapici;
	int		flagvirgo;

	i = 0;
	b = 0;
	flagapici = 0;
	flagvirgo = 0;
	res = malloc (sizeof(char *) * (ft_how_many_words(s) + 1));
	while (s[i])
	{
		if (s[i] != ' ' && (i == 0 || (s[i - 1] == ' '
					&& flagapici == 0 && flagvirgo == 0)))
			res[b++] = ft_crea_parola(s, i);
		if (s[i] == 34 || s[i] == 39)
			ft_change_split_flags(s[i], &flagvirgo, &flagapici);
		i++;
	}
	res[b] = 0;
	return (res);
}
