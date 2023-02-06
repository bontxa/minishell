#include "minishell.h"

char *ft_remove_first_char_from_str(char *str, char c, int count)
{
	int		i;
	char	*res;
	int		b;

	i = 0;
	b = 0;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1 - count));
	while (str[i])
	{
		if (str[i] != c)
		{
			res[b] = str[i];
			b++;
		}
		i++;
	}
	res[b] = 0;
	if (ft_strlen(res) == ft_strlen(str) - 1)
	{
		// printf("entro\n");
		// printf("str = %s\n", str);
		// printf("res = %s\n", res);
		free(str);
	}
	return (res);
}

char	*ft_remove_empty_virgo(char *str)
{
	int		i;
	i =		0;
	char	*res;
	char	c;

	if (str[0] != 39 && str[0] != 34)
	{
		while (str[i])
		{
			if (str[i] == 34 || str[i] == 39)
			{
				c = str[i];
				if (str[i + 1] && str[i + 1] == c)
				{
					res = ft_remove_first_char_from_str(str, c, 2);
					return (res);
				}
			}
			i++;
		}
	}
	return (str);
}


char *ft_gestisci_virgo(char *str)
{
	int		i;
	int		oldlength;
	int		count;
	char	*res;

	i = 0;
	count = 0;
	res = ft_remove_empty_virgo(str);
	oldlength = ft_strlen(res);
	if (res[0] == '"' || res[ft_strlen(res) - 1] == '"')
	{
		res = ft_strtrim(res, "\"");
	}
	if ((int)ft_strlen(res) != oldlength)
	{
		while (res[i])
		{
			if (res[i] == 34)
				count++;
			i++;
		}
		if (count % 2 != 0)
			res = ft_remove_first_char_from_str(res, 34, count);
	}
	else
	{
		if (res[0] == '\'' || res[ft_strlen(res) - 1] == '\'')
		{
			res = ft_strtrim(res, "'");
		}
		while (res[i])
		{
			if (res[i] == 39)
				count++;
			i++;
		}
		if (count % 2 != 0)
		{
			res = ft_remove_first_char_from_str(res, 39, count);
		}
	}
	return (res);
}
