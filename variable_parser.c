#include "minishell.h"

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
}

char	*extract_var(char *s)
{
	int	i;
	int	b;
	int	x;
	int	c;
	char	*res;
	char	*prima;
	char	*dopo;
	char	*tmp;

	i = 0;
	x = 0;
	c = 0;
	while (s[i] != '$' && s[i])
		i++;
	prima = ft_strncpy(s, 0, i);
	if (s[i] == '$')
		i++;
	b = i;
	if (s[b] >= '0' && s[b] <= '9')
	{
		res = malloc(2);
		res[0] = s[b];
		res[1] = '\0';
		b++;
		i++;
	}
	else
	{
		while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
			i++;
		res = malloc (sizeof(char) * (i - b + 1));
		while (b < i)
		{
			res[x] = s[b];
			x++;
			b++;
		}
		res[x] = '\0';
	}
	dopo = ft_strncpy(s, i, ft_strlen(s));
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
