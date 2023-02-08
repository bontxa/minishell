/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:23:57 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/08 17:31:11 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export_b(char *s)
{
	int	i;
	int	countvirgo;

	i = 0;
	countvirgo = 0;
	while (s[i])
	{
		if (i > 0 && s[i - 1] == '=' && countvirgo == 0)
		{
			printf("\"");
			countvirgo++;
		}
		printf("%c", s[i]);
		i++;
	}
	printf("\"");
}

void ft_print_export()
{
	int	i;

	i = 0;
	while (__environ[i] != 0)
	{
		printf("declare -x ");
		ft_print_export_b(__environ[i]);
		printf("\n");
		i++;
	}
}

void	ft_print_env_b(void)
{
	int	i;

	i = 0;
	while (__environ[i] != 0)
	{
		printf("%s\n", __environ[i]);
		i++;
	}
}
