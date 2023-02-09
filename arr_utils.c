/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:04:58 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:05:15 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_how_many_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

char	**ft_dup_arr(char **arr)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_how_many_strings(arr)));
	i = 0;
	while (arr[i] != 0)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_add_string_to_arr(char **arr, char *s)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (ft_how_many_strings(arr) + 1));
	while (arr[i] != 0)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = ft_strdup(s);
	res[i + 1] = 0;
	return (res);
}

char	**ft_remove_string_from_arr(char **arr, int toremove)
{
	int		i;
	int		b;
	char	**res;

	i = 0;
	b = 0;
	res = malloc(sizeof(char *) * (ft_how_many_strings(arr)));
	while (arr[i] != 0)
	{
		if (i != toremove)
		{
			res[b] = ft_strdup(arr[i]);
			b++;
		}
		i++;
	}
	res[b] = 0;
	b = 0;
	while (arr[b] != 0)
	{
		free(arr[b]);
		b++;
	}
	free(arr);
	return (res);
}

// int		ft_is_str_in_arr(char **arr, char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i] != 0)
// 	{

// 	}
// }
