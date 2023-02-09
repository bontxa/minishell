/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:34:42 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:36:58 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*split_s_c_3(char *s, int *i)
{
	int		start;
	char	*res;

	start = *i;
	while (s[*i] != '|' && s[*i] != '<' && s[*i] != '>' && s[*i])
		*i = *i + 1;
	*i = *i - 1;
	res = ft_create_sc_word(s, start, *i);
	return (res);
}

static char	*split_s_c_2(char *s, int *i)
{
	int		start;
	char	*res;

	start = *i;
	if (s[*i + 1] == s[*i])
		*i = *i + 1;
	res = ft_create_sc_word(s, start, *i);
	return (res);
}

char	**split_s_c(char *s)
{
	char	**res;
	int		i;
	int		b;

	i = 0;
	b = 0;
	res = malloc(sizeof(char *) * (how_many_strings_with_s_c(s) + 1));
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			res[b] = split_s_c_2(s, &i);
			b++;
		}
		else
		{
			res[b] = split_s_c_3(s, &i);
			b++;
		}
		i++;
	}
	res[b] = 0;
	return (res);
}

static void	parse_pipe_min_mag_2(char *prompt_str, char **res, int *b)
{
	char	**tmp;
	int		c;

	if (is_there_a_special_char(prompt_str) == 1)
	{
		tmp = split_s_c(prompt_str);
		c = 0;
		while (tmp[c] != 0)
		{
			res[*b] = tmp[c];
			*b = *b + 1;
			c++;
		}
		free(tmp);
	}
	else
	{
		res[*b] = ft_strdup(prompt_str);
		*b = *b + 1;
	}
}

char	**parse_pipe_min_mag(char **prompt)
{
	int		i;
	int		b;
	char	**res;

	i = 0;
	b = 0;
	res = malloc(sizeof (char *) * (how_many_strings(prompt) + 1));
	while (prompt[i] != 0)
	{
		parse_pipe_min_mag_2(prompt[i], res, &b);
		i++;
	}
	res[b] = 0;
	ft_free_strarr(prompt);
	free(prompt);
	return (res);
}
