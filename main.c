#include "minishell.h"

int	exitStatus;

void	ft_clean_list(t_cmd *comandi)
{
	t_cmd	*tmp;
	t_cmd	*tmp_2;

	tmp = comandi;
	while (tmp)
	{
		tmp_2 = tmp->next;
		free (tmp);
		tmp = tmp_2;
	}
}

void	ft_execute_child(t_prg *box, char **envp)
{
	int	exitStatus;
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
		waitpid(pid, &exitStatus, 0);
		printf("exit status = %d\n", exitStatus);
		close(pipa[1]);
		dup2(pipa[0], box->cmds->infile);
		close(pipa[0]);
	}
}

void	ft_the_executer(t_prg *box, char **envp)
{
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

void	ft_print_list(t_prg *box)
{
	int	i;
	t_cmd	*tmp;

	tmp = box->cmds;
	i = 0;
	while (tmp)
	{
		while (tmp->full_cmd[i] != 0)
		{
			printf("%s\n", tmp->full_cmd[i]);
			if (tmp->infile == 1025)
				printf("delimitatore %s\n", tmp->delimiter);
			i++;
		}
		i = 0;
		printf("CAMBIO\n");
		tmp = tmp->next;
	}
}


//PARTE PRINCIPALE DEL PROGRAMMA, STAMPA STALIN

void	ft_print_header()
{
	printf("\033[1;31m	⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣶⣿⣿⣿⣿⣿⣶⣶⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⠿⠿⠿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡿⠃⠀⠀⠀⠀⠀⠈⠉⠁⠀⠀⠈⠙⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡟⢠⠶⠶⣦⣄⠀⠀⣀⣤⣶⡶⢶⣄⠀⠀⢿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡇⢸⡿⢿⣷⡷⠀⠀⢿⣶⠿⠷⠦⣙⡀⠀⢸⣿⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⠉⠉⠀⠀⠀⠀⠉⠒⠒⠂⠈⠁⠀⠀⢿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⢀⠴⣧⣀⣤⣤⣵⣄⠀⠀⠀⠀⠀⠀⢰⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⡇⠀⢠⣮⣴⣷⣶⣿⣷⣶⣬⡂⠀⠀⠀⠀⢀⠞⢽⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢧⢤⣼⣿⣿⠿⡿⠻⠿⣿⣿⣿⣦⡀⠀⠀⣼⠒⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡄⠈⠉⠀⠀⠿⠿⠿⠉⠛⠛⠃⠀⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣵⡀⢀⠀⠀⢀⡠⢀⠀⠀⠀⢀⡀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣦⡉⠐⠚⠳⣿⡗⠒⠊⠁⠀⢀⣾⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⢀⣀⣠⣤⣶⣺⣿⣿⣿⣿⣿⣿⣦⣄⠀⣿⣇⠀⠀⠀⣠⣾⣿⣿⣿⡦⢤⣄⣀⡀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⣴⣮⣩⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⡛⠿⣦⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣭⣉⣓⣶⣄⠀⠀⠀\n");
	printf("⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⣨⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣏⠉⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀\n");
	printf("⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠉⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀\n");
	printf("⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣤⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿\n");
	printf("⠀⠀⠀⠈⠉⠉⠉⠛⠛⠛⠻⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠟⠛⠋⠉⠁⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠛⠿⢿⣿⣿⡿⠿⠛⠛⠋⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\033[1;37m\n");
	printf("			WELCOME TO SOVIETSHELL				\n");

}

//SOSTITUISCE ECHO E ECHO -N

void	ft_simple_echo(char **to_print, int n)
{
	int	tmp;

	tmp = n;
	if (!to_print && n == 1)
		return;
	else
	{
		while (to_print[n] != 0)
		{
			printf("%s", to_print[n]);
			if (to_print[n + 1] != 0)
				printf(" ");
			n++;
		}
	}
	if (tmp == 1)
		printf("\n");
}

//INTERCETTA CTRL + C E NON FA USCIRE DA MINISHELL

void	ft_signal_ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_ctrl_bs(int sig)
{
	(void)sig;
	return ;
}

//MAIN

static void	ft_main_part_3(char **cmd_args, t_prg box, char **envp)
{
	int		pid;

	if (!cmd_args[0])
		rl_redisplay();
	else if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
		exit(0);
	else if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
	{
		if(chdir(cmd_args[1]) == -1)
			printf("cd: no such file or directory: %s\n", cmd_args[1]);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			ft_the_executer(&box, envp);
		else
		{
			waitpid(pid, &exitStatus, 0);
			printf("exit status: %d\n", exitStatus);
		}
	}
}

static char	**ft_main_part_2(char *shell_prompt)
{
	char	*res;
	char **cmd_args;

	signal(SIGINT, ft_signal_ctrl_c);
	signal(SIGQUIT, ft_signal_ctrl_bs);
	res = readline(shell_prompt);
	if (res == NULL)
	{
		printf("signal\n");
		exit (0);
	}
	add_history(res);
	cmd_args = ft_split(res, ' ');
	cmd_args = variable_expander(cmd_args);
	cmd_args = parse_pipe_min_mag(cmd_args);
	return (cmd_args);
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_args;
	//int		pid;
	char	*shell_prompt;
	char	*tmp;
	t_prg	box;

	(void)argc;
	(void)argv;
	print_header();
	exitStatus = 0;
	box.cmds = NULL;
	shell_prompt = ft_strdup("@sovietshell: \033[0;37m");
	tmp = ft_strjoin("\033[1;31m", getenv("LOGNAME"));
	shell_prompt = ft_strjoin(tmp, shell_prompt);
	while (1)
	{
		cmd_args = ft_main_part_2(shell_prompt);
		ft_clean_list(box.cmds);
		box.cmds = NULL;
		ft_add_element(&box.cmds, cmd_args);
		ft_print_list(&box);
		ft_main_part_3(cmd_args, box, envp);
		/* if (!cmd_args[0])
			rl_redisplay();
		else if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
			exit(0);
		else if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		{
			if(chdir(cmd_args[1]) == -1)
				printf("cd: no such file or directory: %s\n", cmd_args[1]);
		}
		else
		{
			pid = fork();
			if (pid == 0)
				ft_the_executer(&box, envp);
			else
			{
				waitpid(pid, &exitStatus, 0);
				printf("exit status: %d\n", exitStatus);
			}
		} */
	}
	return (0);
}

