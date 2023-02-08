/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:48:16 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/08 16:08:41 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_main_part_2_bis(char **cmd_args)
{
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
	{
		if (cmd_args[2] != 0 && cmd_args[1][0] != '|' && cmd_args[1][0] != '>' && cmd_args[1][0] != '<')
		{
			exitStatus = 1;
			return (NULL);
		}
		if (cmd_args[1] && cmd_args[1][0] != '|' && cmd_args[1][0] != '>' && cmd_args[1][0] != '<')
		{
			ft_export_var(cmd_args[1]);
			ft_free_strarr(cmd_args);
			free(cmd_args);
			return (NULL);
		}
	}
	variable_expander(cmd_args);
	cmd_args = parse_pipe_min_mag(cmd_args);
	return (cmd_args);
}


static char	**ft_main_part_2(char *shell_prompt)
{
	char	*res;
	char **cmd_args;

	res = readline(shell_prompt);
	if (res == NULL)
		free_n_exit(res);
	if (res[0] == '\0')
	{
			ft_signal_ctrl_c(0);
			free(res);
			return (NULL);
	}
	add_history(res);
	if (!ft_strncmp(res, "unset", 5))
	{
		ft_unset_var(res);
		free(res);
		return (NULL);
	}
	cmd_args = ft_altro_split(res);
	free(res);
	cmd_args = ft_main_part_2_bis(cmd_args);
	return (cmd_args);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_args;
	char	*shell_prompt;
	char	*tmp;
	t_prg	box;

	(void)argc;
	(void)argv;
	//ft_print_header();
	exitStatus = 0;
	box.cmds = NULL;
	shell_prompt = "@sovietshell: \033[0;37m";
	tmp = ft_strjoin("\033[1;31m", getenv("LOGNAME"));
	shell_prompt = ft_strjoin(tmp, shell_prompt);
	while (1)
	{
		signal(SIGINT, ft_signal_ctrl_c);
		signal(SIGQUIT, ft_signal_ctrl_bs);
		cmd_args = ft_main_part_2(shell_prompt);
		if (cmd_args != NULL)
		{
			ft_clean_list(box.cmds);
			box.cmds = NULL;
			ft_add_element(&box.cmds, cmd_args);
			ft_main_part_3(cmd_args, box, envp);
		}
	}
	exit (exitStatus);
}
