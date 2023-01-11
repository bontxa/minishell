/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:47:52 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/11 18:11:56 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
1 - splittare prompt
2 - analizzare prompt
3 - controllare variabili env ($)
4 - controllare pipe (|)
*/

void	manage_env(char **splitted, char **envp)
{
	int i = 0;
	if ((splitted[0][3] == '\0') || (splitted[0][3] == ' '))
	{
		while(envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	/* else if ((splitted[1] != 0 && splitted[1][0] == '|') || splitted[0][6] == '|')
		printf("GESTISCI PIPE\n"); */
	else
		printf("%s: command not found\n", splitted[0]);
}

void	manage_pwd(char **splitted)
{
	char path[256];
	if (splitted[0][3] == '\0'|| splitted[0][3] == ' ')
		printf("%s\n", getcwd(path, sizeof(path)));
	/* else if ((splitted[1] != 0 && splitted[1][0] == '|') || splitted[0][3] == '|')
		printf("GESTISCI PIPE\n"); */
	else
		printf("%s: command not found\n", splitted[0]);
}

int ft_cmp(char *s1, char *s2, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}


int main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**splitted;
	(void) argc;
	(void) argv;
	while (1)
	{
		prompt = readline("minishell$ ");
		splitted = ft_split(prompt, ' ');
		//printf("%s\n", getenv(prompt));
		add_history (prompt);
		if (ft_cmp(prompt, "cd ", 3))
			printf("%s\n", prompt);
		if (ft_cmp(prompt, "echo ", 5))
			printf("%s\n", prompt);
		if (ft_cmp(prompt, "pwd", 3))
			manage_pwd(splitted);
		if (ft_cmp(prompt, "export", 6))
			printf("%s\n", prompt);
		if (ft_cmp(prompt, "unset", 5))
			printf("%s\n", prompt);
		if (ft_cmp(prompt, "env", 3))
			manage_env(splitted, envp);
		if (ft_cmp(prompt, "exit", 4))
			printf("%s\n", prompt);
	}

}
