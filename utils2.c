/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:16:27 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:23:38 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_there_a_dollar(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != '\0' && s[i +1] != ' ' && s[i + 1] != 34)
			return (1);
		i++;
	}
	return (0);
}

void	variable_expander(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != 0)
	{
		if (ft_is_var_inside_quotes(prompt[i]) == 0)
		{
			while (is_there_a_dollar(prompt[i]) == 1)
				prompt[i] = ft_extract_var(prompt[i]);
			i++;
		}
		else
			i++;
	}
}

static int	countwords(char const *s, char c)
{
	int	count;
	int	i;
	int	flag;

	count = 0;
	i = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static char	*create_word(char const *s, char c, int start)
{
	char	*newword;
	int		i;
	int		startcpy;

	i = 0;
	startcpy = start;
	while (s[start] != c && s[start] != '\0')
	{
		i++;
		start++;
	}
	newword = malloc (sizeof(char) * i + 1);
	i = 0;
	if (!newword)
		return (NULL);
	while (s[startcpy] != c && s[startcpy] != '\0')
	{
		newword[i] = s[startcpy];
		i++;
		startcpy++;
	}
	newword[i] = '\0';
	return (newword);
}

char	**ft_simple_split(char const *s, char c)
{
	char	**strarr;
	int		i;
	int		b;
	int		flag;

	strarr = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (!strarr)
		return (NULL);
	i = 0;
	b = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			strarr[b] = create_word(s, c, i);
			b++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	strarr[b] = NULL;
	return (strarr);
}
