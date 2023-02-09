/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:46:32 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:46:44 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	howlong(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	int		i;

	i = howlong(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	newstr = (char *)malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		newstr[0] = '-';
	}
	newstr[i] = '\0';
	i--;
	while (n > 9)
	{
		newstr[i] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	newstr[i] = n + '0';
	return (newstr);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (8);
	return (0);
}

int	ft_is_valid_var_name(char *s)
{
	int	i;

	i = 0;
	if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		i++;
	else
		return (0);
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
