#include "minishell.h"

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

static size_t	count_c_s(char const *s1, char const *set)
{
	size_t	i;
	size_t	res;
	size_t	x;

	i = 0;
	res = 0;
	x = 0;
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			res++;
			x = 0;
			i++;
		}
		else
			x++;
	}
	return (res);
}

static size_t	count_c_e(char const *s1, char const *set)
{
	size_t	i;
	size_t	x;
	size_t	res;

	x = 0;
	i = ft_strlen(s1) - 1;
	res = ft_strlen(s1);
	while (set[x])
	{
		if (s1[i] == set[x])
		{
			res--;
			x = 0;
			i--;
		}
		else
			x++;
	}
	return (res);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*newstr;
	size_t		i;
	size_t		last;
	size_t		first;

	i = 0;
	first = count_c_s(s1, set);
	last = count_c_e(s1, set);
	if (s1[first] == '\0')
	{
		first = 0;
		last = 0;
	}
	newstr = (char *) malloc(sizeof(char) * (last - first + 1));
	if (!newstr)
		return (NULL);
	while (first < last)
	{
		newstr[i] = s1[first];
		i++;
		first++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		b;
	char	*newstr;

	i = 0;
	b = 0;
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	while (s1[b])
	{
		newstr[i] = s1[b];
		i++;
		b++;
	}
	b = 0;
	while (s2[b])
	{
		newstr[i] = s2[b];
		i++;
		b++;
	}
	newstr[i] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*newstr;

	i = ft_strlen(s);
	newstr = malloc(sizeof(char) * i + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
