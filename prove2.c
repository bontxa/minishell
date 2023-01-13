#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

char	*ft_strncpy(char *s, int start, int finish)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (finish - start + 1));
	while (start < finish)
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
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
		return (res);
	}
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
	dopo = ft_strncpy(s, i, ft_strlen(s));
	res = ft_strjoin(prima, getenv(res));
	res = ft_strjoin(res, dopo);
	return (res);
}
