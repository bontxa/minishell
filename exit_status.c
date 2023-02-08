/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:03:50 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/08 18:28:53 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_good_exit_status(char *s)
{
	int	i;

	i = 1;
	if ((s[0] > '9' || s[0] < '0') && s[0] != '-' && s[0] != '+')
		return (1);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_change_flag(char c, int *flag, int *i)
{
	if (c == 34)
		*flag = 1;
	if (c == 39)
		*flag = 2;
	*i = *i + 1;
}

static char	*ft_create_res(char *s, char *res)
{
	int	i;
	int	b;
	int	flag;

	i = 0;
	b = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && flag == 0)
			ft_change_flag(s[i], &flag, &i);
		else if ((s[i] == 34 && flag == 1) || (s[i] == 39 && flag == 2))
			i++;
		else
		{
			res[b] = s[i];
			b++;
			i++;
		}
	}
	res[b] = '\0';
	return (res);
}

static int	ft_remove_virgo_exit_status_count(char *s)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && flag == 0)
			ft_change_flag(s[i], &flag, &i);
		else if ((s[i] == 34 && flag == 1) || (s[i] == 39 && flag == 2))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*ft_remove_virgo_exit_status(char *s)
{
	int		count;
	char	*res;

	count = ft_remove_virgo_exit_status_count(s);
	res = malloc(sizeof(char) * count + 1);
	res = ft_create_res(s, res);
	return (res);
}
