/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:50:51 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/07 10:32:50 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*extract_var_4(char *s, char *res, int *i, char	*prima)
{
	char	*dopo;
	char	*tmp;
	char	*tmp2;

	dopo = ft_strncpy(s, *i, ft_strlen(s));
	if (res[0] == '\0')
	{
		tmp = ft_itoa(exitStatus);
	}
	else
	{
		tmp = getenv(res);
		if (!tmp)
		{
			tmp = malloc(1);
			tmp[0] = '\0';
		}
	}
	res = ft_strjoin(prima, tmp);
	free(prima);
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

static char	*extract_var_3(char *s, int *i, int *b)
{
	int	x;
	char	*res;

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
	return (res);
}

static char	*extract_var_2(char *s, int *i, int *b)
{
	char	*res;

	res = malloc(2);
	res[0] = s[*b];
	res[1] = '\0';
	*b = *b + 1;
	*i = *i + 1;
	return (res);
}

char	*extract_var(char *s)
{
	int		i;
	int		b;
	char	*res;
	char	*prima;
	char	*tmp;

	i = 0;
	res = NULL;
	while (s[i] != '$' && s[i])
		i++;
	prima = ft_strncpy(s, 0, i);
	if (s[i] == '$')
		i++;
	b = i;
	if (s[b] == '?')
	{
		i++;
		res = malloc(2);
		res[0] = '\0';
		return (extract_var_4(s, res, &i, prima));
	}
	if (s[b] >= '0' && s[b] <= '9')
		res = extract_var_2(s, &i, &b);
	else
		res = extract_var_3(s, &i, &b);
	tmp = extract_var_4(s, res, &i, prima);
	free(res);
	return (tmp);
}
