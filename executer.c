/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:22 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:38:44 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_there_a_pipe(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_there_virgos(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

void	ft_clean_list(t_cmd *comandi)
{
	t_cmd	*tmp;
	t_cmd	*tmp_2;

	tmp = comandi;
	while (tmp)
	{
		tmp_2 = tmp->next;
		ft_free_strarr(tmp->full_cmd);
		if (tmp->infile > 0)
			close(tmp->infile);
		if (tmp->outfile > 1)
			close(tmp->outfile);
		free(tmp->full_cmd);
		free (tmp);
		tmp = tmp_2;
	}
}

static void	ft_execute_child(t_prg *box, char **envp)
{
	int	pipa[2];
	int	pid;

	pipe(pipa);
	pid = fork();
	if (pid == 0)
	{
		close(pipa[0]);
		dup2(pipa[1], 1);
		close(pipa[1]);
		execute_cmd(box->cmds->full_cmd, envp);
	}
	else
	{
		waitpid(pid, &g_exitstatus, WNOHANG);
		close(pipa[1]);
		dup2(pipa[0], 0);
		close(pipa[0]);
	}
}

void	ft_the_executer(t_prg *box, char **envp)
{
	if (box->cmds->infile < 0)
		exit(2);
	if (box->cmds->infile == 1025)
		here_doc_handler(box->cmds->delimiter);
	else
		dup2(box->cmds->infile, 0);
	while (box->cmds->next)
	{
		ft_execute_child(box, envp);
		box->cmds = box->cmds->next;
	}
	dup2(box->cmds->outfile, 1);
	execute_cmd(box->cmds->full_cmd, envp);
}
