#include "minishell.h"

static int		ft_how_many_strings(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

char	**ft_dup_arr(char **arr)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (ft_how_many_strings(arr)));
	i = 0;
	while (arr[i] != 0)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_add_string_to_arr(char **arr, char *s)
{
	int		i;
	char	**res;

	i = 0;
	res = malloc(sizeof(char *) * (ft_how_many_strings(arr) + 1));
	while (arr[i] != 0)
	{
		res[i] = ft_strdup(arr[i]);
		i++;
	}
	res[i] = ft_strdup(s);
	res[i + 1] = 0;
	return (res);
}

char	**ft_remove_string_from_arr(char **arr, char *str)
{
	int		i;
	int		b;
	char	**res;

	i = 0;
	b = 0;
	res = malloc(sizeof(char *) * (ft_how_many_strings(arr)));
	//str = ft_strjoin(str, "=");
	while (arr[i] != 0)
	{
		if (ft_strncmp(arr[i], str, ft_strlen(str)) != 0)
		{
			res[b] = ft_strdup(arr[i]);
			b++;
		}
		i++;
	}
	res[b] = 0;
	b = 0;
	while (arr[b] != 0)
	{
		free(arr[b]);
		b++;
	}
	free(arr);
	return(res);
}

// int		ft_is_str_in_arr(char **arr, char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i] != 0)
// 	{

// 	}
// }
