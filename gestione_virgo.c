/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestione_virgo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:34:41 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:35:04 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remove_first_char_from_str(char *str, char c, int count)
{
	int		i;
	char	*res;
	int		b;

	i = 0;
	b = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1 - count));
	while (str[i])
	{
		if (str[i] != c)
		{
			res[b] = str[i];
			b++;
		}
		i++;
	}
	res[b] = 0;
	if (ft_strlen(res) == ft_strlen(str) - 1)
		free(str);
	return (res);
}

static char	*ft_remove_empty_virgo(char *str)
{
	int		i;
	char	*res;
	char	c;

	i = 0;
	if (str[0] != 39 && str[0] != 34)
	{
		while (str[i])
		{
			if (str[i] == 34 || str[i] == 39)
			{
				c = str[i];
				if (str[i + 1] && str[i + 1] == c)
				{
					res = ft_remove_first_char_from_str(str, c, 2);
					return (res);
				}
			}
			i++;
		}
	}
	return (str);
}

static char	*ft_gestisci_virgo_2(char *res, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (res[i])
	{
		if (res[i] == c)
			count++;
		i++;
	}
	if (count % 2 != 0)
		res = ft_remove_first_char_from_str(res, c, count);
	return (res);
}

char	*ft_gestisci_virgo(char *str)
{
	int		oldlength;
	char	*res;

	res = ft_remove_empty_virgo(str);
	oldlength = ft_strlen(res);
	if (res[0] == '"' || res[ft_strlen(res) - 1] == '"')
		res = ft_strtrim(res, "\"");
	if ((int)ft_strlen(res) != oldlength)
		res = ft_gestisci_virgo_2(res, 34);
	else
	{
		if (res[0] == '\'' || res[ft_strlen(res) - 1] == '\'')
			res = ft_strtrim(res, "'");
		res = ft_gestisci_virgo_2(res, 39);
	}
	return (res);
}
