/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:35:38 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 11:35:44 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	do_here_doc(char *delim, int *pipa)
{
	char	*linea;
	char	*delimiter;

	delimiter = ft_strjoin(delim, "\n");
	close(pipa[0]);
	linea = get_next_line(0);
	while (linea)
	{
		if (!ft_strncmp(linea, delimiter, ft_strlen(delimiter) + 1))
		{
			close(1);
			free(linea);
			free(delimiter);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(linea, pipa[1]);
		free(linea);
		linea = get_next_line(0);
	}
	close(1);
	free(linea);
	free(delimiter);
}

void	here_doc_handler(char *delim)
{
	int	pid;
	int	pipa[2];

	pipe(pipa);
	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(pipa[1]);
		dup2(pipa[0], 0);
		close(pipa[0]);
	}
	else
		do_here_doc(delim, pipa);
}
