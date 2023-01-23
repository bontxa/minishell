#include "minishell.h"
#include <stdio.h>

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

// //ESTRAE IL NOME DELLA VARIABILE TOGLIENDO IL SEGNO $

// char	*get_var_name(char *s)
// {
// 	int		i;
// 	int		b;
// 	char	*res;

// 	b = 0;
// 	i = 0;
// 	while (s[i] != '$')
// 		i++;
// 	i++;
// 	res = (char *) malloc(sizeof(char) * (ft_strlen(s) - i + 1));
// 	while (s[i] && s[i] != ' ')
// 	{
// 		res[b] = s[i];
// 		i++;
// 		b++;
// 	}
// 	res[b] = '\0';
// 	return (res);
// }

// int		is_ok_in_var_name(char *s)
// {
// 	int	i;
// 	int	b;
// 	int	x;
// 	char	*res;

// 	i = 0;
// 	x = 0;
// 	while (s[i] != '$' && s[i])
// 		i++;
// 	if (s[i] == '$')
// 		i++;
// 	b = i;
// 	if (s[b] >= '0' && s[b] <= '9')
// 	{
// 		res = malloc(2);
// 		res[0] = s[b];
// 		res[1] = '\0';
// 		return (res);
// 	}
// 	while ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_')
// 		i++;
// 	res = malloc (sizeof(char) * (i - b + 1));
// 	while (b < i)
// 	{
// 		res[x] = s[b];
// 		x++;
// 		b++;
// 	}
// 	res[x] = '\0';
// 	return (res);
// }

//SE VOLESSIMO IMPLEMENTARE ANCHE IL ~

// int		is_there_a_tilde(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '~')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*expand_tilde(char *s)
// {

// }
// char	extract_dollar(char *s)
// {
// 	$PWDciao
// }
//ESPANDE LE VARIABILI $NOME
//CONTROLLARE echo ciao$USER

int		how_many_strings_with_s_c(char *s)
{
	int	i;
	int	res;
	int	flag;

	i = 0;
	res = 0;
	flag = 1;

	while (s[i])
	{
		if (s[i] == '|' || s[i] == '>' || s[i] == '<')
			flag = 1;
		if (s[i] != '|' && s[i] != '>' && s[i] != '<' && flag == 1)
		{
			res++;
			flag = 0;
		}
		i++;
	}
	return (res);
}



int		how_many_special_chars(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == '|' || (s[i] == '>' && s[i - 1] != '>') || (s[i] == '<' && s[i - 1] != '<'))
			res++;
		i++;
	}
	return (res);
}



int		is_there_a_special_char(char *s)
{
	int	i;

	i = 0;
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

int		is_there_other_chars(char *s)
{
	int	i;
	i = 0;

	while (s[i])
	{
		if (s[i] != '|' && s[i] != '>' && s[i] != '<')
			return (1);
		i++;
	}
	return (0);
}





int		how_many_strings(char **prompt)
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

char	**parse_pipe_min_mag(char **prompt)
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
			tmp = split_for_special_chars(prompt[i]);
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
}


// char	**variable_expander(char **prompt)
// {
// 	int		i;

// 	i = 0;
// 	while (prompt[i] != 0)
// 	{
// 		while (is_there_a_dollar(prompt[i]) == 1)
// 		{
// 			// "$PWD 'hola'"
// 			// "'hola' $PWD"
// 			// "$PWD/hola"
// 			prompt[i] = extract_var(prompt[i]);
// 		}

// 		i++;
// 	}
// 	return (prompt);
// }

// int	main(int argc, char **argv)
// {
// 	char	**cmd;
// 	int		i;

// 	(void) argc;
// 	i = 0;
// 	cmd = ft_split(argv[1], ' ');
// 	cmd = variable_expander(cmd);
// 	while (cmd[i] != 0)
// 	{
// 		printf("%s\n", cmd[i]);
// 		i++;
// 	}
// }
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	**res;
	int		i;

	i = 0;
	res = parse_pipe_min_mag(argv);
	while (res[i] != 0)
	{
		printf("%s\n", res[i]);
		i++;
	}

}
