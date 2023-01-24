/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:50:51 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/24 13:23:20 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
//CONTROLLA SE C'E` UN $

int		is_there_a_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}


char	**variable_expander(char **prompt)
{
	int		i;

	i = 0;
	while (prompt[i] != 0)
	{
		while (is_there_a_dollar(prompt[i]) == 1)
		{
			// "$PWD 'hola'"
			// "'hola' $PWD"
			// "$PWD/hola"
			prompt[i] = extract_var(prompt[i]);
		}

		i++;
	}
	return (prompt);
} */

static char	*extract_var_4(char *s, char *res, int *i, char	*prima)
{
	char	*dopo;
	char	*tmp;

	dopo = ft_strncpy(s, *i, ft_strlen(s));
	tmp = getenv(res);
	if (!tmp)
	{
		tmp = malloc(1);
		tmp[0] = '\0';
	}
	res = ft_strjoin(prima, tmp);
	res = ft_strjoin(res, dopo);
	return (res);
}

static void	extract_var_3(char *s, char *res, int *i, int *b)
{
	int	x;

	x = 0;
	while ((s[*i] >= 'a' && s[*i] <= 'z') || (s[*i] >= 'A' && s[*i] <= 'Z')
		|| (s[*i] >= '0' && s[*i] <= '9') || s[*i] == '_')
		*i = *i + 1;
	res = malloc (sizeof(char) * (*i - *b + 1));
	while (*b < *i)
	{
		res[x] = s[*b];
		x++;
		*b = *b + 1;
	}
	res[x] = '\0';
}

static void	extract_var_2(char *s, char *res, int *i, int *b)
{
	res = malloc(2);
	res[0] = s[*b];
	res[1] = '\0';
	*b = *b + 1;
	*i = *i + 1;
}

char	*extract_var(char *s)
{
	int		i;
	int		b;
	char	*res;
	char	*prima;

	i = 0;
	res = NULL;
	while (s[i] != '$' && s[i])
		i++;
	prima = ft_strncpy(s, 0, i);
	if (s[i] == '$')
		i++;
	b = i;
	if (s[b] >= '0' && s[b] <= '9')
		extract_var_2(s, res, &i, &b);
	else
		extract_var_3(s, res, &i, &b);
	return (extract_var_4(s, res, &i, prima));
}
