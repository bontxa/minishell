/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:25:35 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:30:19 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extact_var_free(char *dopo, char *tmp2, char *res, char *s)
{
	if (dopo[0] != '\0')
	{
		tmp2 = ft_strjoin(res, dopo);
		free (s);
		free(res);
		free(dopo);
		return (tmp2);
	}
	free(s);
	free(dopo);
	return (res);
}

char	*ft_ft_extract_var_getenv(char *res, int *flag)
{
	char	*tmp;

	tmp = getenv(res);
	if (!tmp)
	{
		tmp = malloc(1);
		tmp[0] = '\0';
		*flag = 1;
	}
	return (tmp);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		segno;
	int		nbr;

	i = 0;
	segno = 1;
	nbr = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
		segno = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - 48;
		i++;
	}
	return (nbr * segno);
}
