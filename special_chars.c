/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:05:11 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/03 12:26:22 by ltombell         ###   ########.fr       */
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

/* static char	*split_s_c_3(char *s, int *i)
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
	int		start;

	i = 0;
	b = 0;
	start = 0;
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
	return (res);
} */

/* char	**split_s_c(char *s)
{
	char	**res;
	int		i;
	int		flag;
	int		b;
	int		start;

	i = 0;
	b = 0;
	start = 0;
	flag = 1;
	res = malloc(sizeof(char *) * (how_many_strings_with_s_c(s) + 1));
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			start = i;
			if (s[i + 1] == s[i])
				i++;
			res[b] = ft_create_sc_word(s, start, i);
			b++;
		}
		else
		{
			start = i;
			while (s[i] != '|' && s[i] != '<' && s[i] != '>' && s[i])
				i++;
			i--;
			res[b] = ft_create_sc_word(s, start, i);
			b++;
		}
		i++;
	}
	res[b] = 0;
	return (res);
} */
/*char	**parse_pipe_min_mag(char **prompt)
{
	int		i;
	int		b;
	int		c;
	char	**res;
	char	**tmp;

	i = 0;
	b = 0;
	res = malloc(sizeof (char *) * (how_many_strings(prompt) + 1));
	while (prompt[i] != 0)
	{
		if (is_there_a_special_char(prompt[i]) == 1)
		{
			tmp = split_s_c(prompt[i]);
			c = 0;
			while (tmp[c] != 0)
			{
				res[b] = tmp[c];
				b++;
				c++;
			}
		}
		else
		{
			res[b] = ft_strdup(prompt[i]);
			b++;
		}
		i++;
	}
	res[b] = 0;
	return (res);
} */

// int	main(int argc, char **argv)
// {
// 	char	**res;

// 	// printf("%d\n", how_many_strings_with_s_c("|mimmo|mommo"));
// 	res = parse_pipe_min_mag(argv);
// 	int i = 0;
// 	while (res[i] != 0)
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// }
