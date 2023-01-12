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

//ESTRAE IL NOME DELLA VARIABILE TOGLIENDO IL SEGNO $

char	*get_var_name(char *s)
{
	int		i;
	int		b;
	char	*res;

	b = 0;
	i = 0;
	while (s[i] != '$')
		i++;
	i++;
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	while (s[i] && s[i] != ' ')
	{
		res[b] = s[i];
		i++;
		b++;
	}
	res[b] = '\0';
	return (res);
}

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

//ESPANDE LE VARIABILI $NOME

char	**variable_expander(char **prompt)
{
	int	i;

	i = 0;
	while (prompt[i] != 0)
	{
		if (is_there_a_dollar(prompt[i]) == 1)
			prompt[i] = getenv(get_var_name(prompt[i]));
		i++;
	}
	return (prompt);
}

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
