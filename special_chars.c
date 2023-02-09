/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:05:11 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:38:06 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	how_many_special_chars(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == '|' || (s[i] == '>' && (i > 0 && s[i - 1] != '>'))
			|| (s[i] == '<' && (i > 0 && s[i - 1] != '<')))
			res++;
		i++;
	}
	return (res);
}

int	is_there_a_special_char(char *s)
{
	int	i;

	i = 0;
	if (s[0] == 34 || s[0] == 39)
		return (0);
	while (s[i])
	{
		if (s[i] == ' ')
			return (0);
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	how_many_strings_with_s_c(char *s)
{
	int		i;
	int		res;
	int		flag;

	i = 0;
	res = 0;
	flag = 1;
	while (s[i])
	{
		if ((s[i] == '>' && s[i + 1] != '>' ) || s[i] == '|'
			|| (s[i] == '<' && s[i + 1] != '<'))
		{
			res++;
			flag = 1;
		}
		else if (s[i] != '>' && s[i] != '|' && s[i] != '<' && flag == 1)
		{
			res++;
			flag = 0;
		}
		i++;
	}
	return (res);
}

int	how_many_strings(char **prompt)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (prompt[i] != 0)
	{
		if (is_there_a_special_char(prompt[i]) == 1)
		{
			res += how_many_special_chars(prompt[i]);
			res += how_many_strings_with_s_c(prompt[i]);
		}
		else
			res += 1;
		i++;
	}
	return (res);
}

char	*ft_create_sc_word(char *s, int start, int i)
{
	int		a;
	char	*res;

	res = malloc(sizeof(char) * i - start + 2);
	a = 0;
	while (start <= i)
	{
		res[a] = s[start];
		start++;
		a++;
	}
	res[a] = '\0';
	return (res);
}
