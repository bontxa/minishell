/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:50:51 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:56:02 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_extract_var_4(char *s, char *res, int *i, char *prima)
{
	char	*dopo;
	char	*tmp;
	char	*tmp2;
	int		flag;

	flag = 0;
	tmp2 = NULL;
	dopo = ft_strncpy(s, *i, ft_strlen(s));
	if (res[0] == '\0')
	{
		tmp = ft_itoa(g_exitstatus);
		flag = 1;
	}
	else
		tmp = ft_ft_extract_var_getenv(res, &flag);
	res = ft_strjoin(prima, tmp);
	free(prima);
	if (flag == 1)
		free(tmp);
	return (ft_extact_var_free(dopo, tmp2, res, s));
}

static char	*ft_ft_extract_var_3(char *s, int *i, int *b)
{
	int		x;
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

static char	*ft_ft_extract_var_2(char *s, int *i, int *b)
{
	char	*res;

	res = malloc(2);
	res[0] = s[*b];
	res[1] = '\0';
	*b = *b + 1;
	*i = *i + 1;
	return (res);
}

char	*ft_extract_g_exitstatus(int *i, char *s, char *prima)
{
	char	*res;
	char	*tmp;

	*i = *i + 1;
	res = malloc(1);
	res[0] = '\0';
	tmp = ft_extract_var_4(s, res, i, prima);
	free(res);
	return (tmp);
}

char	*ft_extract_var(char *s)
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
		return (ft_extract_g_exitstatus(&i, s, prima));
	if (s[b] >= '0' && s[b] <= '9')
		res = ft_ft_extract_var_2(s, &i, &b);
	else
		res = ft_ft_extract_var_3(s, &i, &b);
	tmp = ft_extract_var_4(s, res, &i, prima);
	free(res);
	return (tmp);
}
