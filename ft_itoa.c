#include "minishell.h"

static int	howlong(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	int		i;

	i = howlong(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	newstr = (char *)malloc(sizeof(char) * (i + 1));
	if (!newstr)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		newstr[0] = '-';
	}
	newstr[i] = '\0';
	i--;
	while (n > 9)
	{
		newstr[i] = (n % 10) + '0';
		i--;
		n /= 10;
	}
	newstr[i] = n + '0';
	return (newstr);
}
