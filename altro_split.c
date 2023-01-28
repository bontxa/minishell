#include "minishell.h"

int	ft_how_many_words(char *s)
{
	int	i;
	int	flagApici;
	int	flagVirgo;
	int	count;

	i = 0;
	flagApici = 0;
	flagVirgo = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ((s[i - 1] == ' ' && flagApici == 0 && flagVirgo == 0) || i == 0))
		{
			count++;
		}
		if (s[i] == 34)
		{
			if (flagVirgo == 0)
				flagVirgo = 1;
			else
				flagVirgo = 0;
		}
		if (s[i] == 39)
		{
			if (flagApici == 0)
				flagApici = 1;
			else
				flagApici = 0;
		}
		i++;
	}
	//printf("prima di splittare ho contato %d parole\n", count);
	return (count);
}

char	*ft_crea_parola(char *s, int i)
{
	int		b;
	int		flagApici;
	int		flagVirgo;
	char	*res;
	int		c;

	flagApici = 0;
	flagVirgo = 0;
	b = i;
	c = 0;
	while (s[i])
	{
		if (s[i] == ' ' && flagApici == 0 && flagVirgo == 0)
		{
			i--;
			break;
		}
		if (s[i] == 34)
		{
			if (flagVirgo == 0)
				flagVirgo = 1;
			else
				flagVirgo = 0;
		}
		if (s[i] == 39)
		{
			if (flagApici == 0)
				flagApici = 1;
			else
				flagApici = 0;
		}
		i++;
	}
	res = malloc(sizeof(char) * (i - b + 1));
	while (b <= i)
	{
		res[c] = s[b];
		b++;
		c++;
	}
	res[c] = 0;
	return (res);
}

char	**ft_altro_split(char *s)
{
	char	**res;
	int		i;
	int		b;
	int		flagApici;
	int		flagVirgo;

	i = 0;
	b = 0;
	flagApici = 0;
	flagVirgo = 0;
	res = malloc (sizeof(char *) * (ft_how_many_words(s) + 1));
	while (s[i])
	{
		if (s[i] != ' ' && ((s[i - 1] == ' ' && flagApici == 0 && flagVirgo == 0) || i == 0))
		{
			res[b] = ft_crea_parola(s, i);
			b++;
		}
		if (s[i] == 34)
		{
			if (flagVirgo == 0)
				flagVirgo = 1;
			else
				flagVirgo = 0;
		}
		if (s[i] == 39)
		{
			if (flagApici == 0)
				flagApici = 1;
			else
				flagApici = 0;
		}
		i++;
	}
	res[b] = 0;
	// int x = 0;
	// while (res[x] != 0)
	// {
	// 	printf("dallo split %s\n", res[x]);
	// 	x++;
	// }
	return (res);
}

// int	main(int argc, char **argv)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
// 	printf("%d\n", ft_how_many_words(argv[1]));
// 	res = ft_altro_split(argv[1]);
// 	while (res[i] != 0)
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// }
