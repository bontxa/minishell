/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:59:35 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:39:19 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_echo(char **to_print, int n)
{
	int	tmp;
	int	flag;

	tmp = n;
	flag = 0;
	if (!to_print && n == 1)
		return ;
	else
	{
		while (to_print[n] != 0)
		{
			if (ft_strncmp(to_print[n], "-n", 2) != 0 || flag == 1)
			{
				printf("%s", to_print[n]);
				flag = 1;
				if (to_print[n + 1] != 0)
					printf(" ");
			}
			n++;
		}
	}
	if (tmp == 1)
		printf("\n");
}

static void	ft_free_clean_exit(t_cmd *cmds, char **cmd_args)
{
	ft_clean_list(cmds);
	ft_free_strarr(cmd_args);
	free(cmd_args);
	exit(g_exitstatus);
}

void	ft_others(char **cmd_args, t_prg box, char **envp)
{
	int	pid;
	int	flagexit;

	flagexit = 0;
	ft_free_strarr(cmd_args);
	free(cmd_args);
	pid = fork();
	if (pid == 0)
		ft_the_executer(&box, envp);
	else
	{
		if (g_exitstatus == 1)
			flagexit = 1;
		waitpid(pid, &g_exitstatus, 0);
		if (flagexit == 1)
			g_exitstatus = 1;
	}
}

void	ft_cd(char **cmd_args)
{
	if (cmd_args[2] == 0)
	{
		if (chdir(cmd_args[1]) == -1)
		{
			write(2, "no such file or directory\n", 27);
			g_exitstatus = 1;
		}
		else
			g_exitstatus = 0;
	}
	else
	{
		write(2, " too many arguments\n", 20);
		g_exitstatus = 1;
	}
	ft_free_strarr(cmd_args);
	free(cmd_args);
}

void	ft_exit(char **cmd_args, t_prg box)
{
	char	*tmp;

	if (cmd_args[1] == 0)
		ft_free_clean_exit(box.cmds, cmd_args);
	else if (cmd_args[1] != 0 && cmd_args[2] == 0)
	{
		tmp = ft_remove_virgo_exit_status(cmd_args[1]);
		if (ft_is_good_exit_status(tmp) == 0)
			g_exitstatus = ft_atoi(tmp);
		else
		{
			write(2, "wrong exit status\n", 19);
			g_exitstatus = 2;
		}
		ft_free_clean_exit(box.cmds, cmd_args);
	}
	else if (cmd_args[2] != 0)
	{
		write (2, "exit: too many arguments\n", 26);
		g_exitstatus = 1;
		ft_free_strarr(cmd_args);
		free(cmd_args);
	}
}
