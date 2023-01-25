/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:07:52 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/25 13:06:39 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_remove_from_arr(char **full_cmd, int i)
{
	int	b;
	char **res;

	b = 0;
	i++;
	while (full_cmd[b] != 0)
		b++;
	res = malloc(sizeof(char *) * (b - i + 1));
	b = 0;
	while (full_cmd[i] != 0)
		res[b++] = ft_strdup(full_cmd[i++]);
	res[b] = 0;
	return (res);
}

static void	ft_check_for_minus_3(t_cmd *elem, int i)
{
	if (elem->full_cmd[i - 1])
	{
		elem->infile = open(elem->full_cmd[i - 1], O_RDONLY);
		if (elem->infile < 0)
			printf("unable to open file\n");
	}
	else
	{
		printf("errore nell'infile, parametro scorretto");
		exit(-1);
	}
	elem->full_cmd = ft_remove_from_arr(elem->full_cmd, i);
}

static void	ft_check_for_minus_2(t_cmd *elem, int i)
{
	elem->infile = 1025;
	elem->delimiter = ft_strdup(elem->full_cmd[i + 1]);
	elem->full_cmd = ft_remove_from_arr(elem->full_cmd, i +1);
}

void	ft_check_for_minus(t_cmd *elem)
{
	int	i;

	i = 0;
	while (elem->full_cmd[i] != 0)
	{
		if (elem->full_cmd[i][0] == '<')
		{
			if (elem->full_cmd[i][1] && elem->full_cmd[i][1] == '<')
				ft_check_for_minus_2(elem, i);
			else
				ft_check_for_minus_3(elem, i);
		}
		i++;
	}
}