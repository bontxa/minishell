#include "minishell.h"

void	free_n_exit(char *res)  ////// gia' spostata
{
	free(res);
	exit (0);
}

int	exitStatus;

int		is_there_virgos(char *str)////////SPOSTATA
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return(1);
		i++;
	}
	return (0);
}

void    ft_free_strarr(char **strarr)////////////SPOSTATA
{
    int i;
    i = 0;
    while(strarr[i])
    {
        free(strarr[i]);
        i++;
    }
    //free(strarr);
}

int		ft_is_good_exit_status(char *s)//////////////////SPOSTATA INIZIO
{
	int	i;

	i = 1;
	if ((s[0] > '9' || s[0] < '0') && s[0] != '-' && s[0] != '+')
		return (1);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_change_flag(char c, int *flag, int *i)
{
	if (c == 34)
		*flag = 1;
	if (c == 39)
		*flag = 2;
	*i = *i + 1;
}

static char	*ft_create_res(char *s, char *res)
{
	int	i;
	int	b;
	int	flag;

	i = 0;
	b = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && flag == 0)
			ft_change_flag(s[i], &flag, &i);
		else if ((s[i] == 34 && flag == 1) || (s[i] == 39 && flag == 2))
			i++;
		else
		{
			res[b] = s[i];
			b++;
			i++;
		}
	}
	res[b] = '\0';
	return (res);
}

int	ft_remove_virgo_exit_status_count(char *s)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] == 34 || s[i] == 39) && flag == 0)
			ft_change_flag(s[i], &flag, &i);
		else if ((s[i] == 34 && flag == 1) || (s[i] == 39 && flag == 2))
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	*ft_remove_virgo_exit_status(char *s)//////////SPOSTATA FINE
{
	int		count;
	char	*res;

	count = ft_remove_virgo_exit_status_count(s);
	res = malloc(sizeof(char) * count + 1);
	res = ft_create_res(s, res);
	return (res);
}

void	ft_print_export_b(char *s)///////////////////////SPOSTATA
{
	int	i;
	int	countVirgo;

	i = 0;
	countVirgo = 0;
	while (s[i])
	{
		if (i > 0 && s[i - 1] == '=' && countVirgo == 0)
		{
			printf("\"");
			countVirgo++;
		}
		// if (s[i + 1] == '\0')
		// {
		// 	printf("\"");
		// }
		printf("%c", s[i]);
		i++;
	}
	printf("\"");
}

void ft_print_export()/////////////////////SPOSTATA
{
	int	i;

	i = 0;
	while (__environ[i] != 0)
	{
		printf("declare -x ");
		ft_print_export_b(__environ[i]);
		printf("\n");
		i++;
	}
}

// void	ft_print_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i] != 0)
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

//CONTROLLA SE LE VARIABILI VANNO ESPANSE

int		ft_is_var_inside_quotes(char *s)//////////////COPIATA INIZIO
{
	int	i;
	int	flagApici;

	flagApici = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			if (flagApici == 1)
				flagApici = 0;
			else
				flagApici = 1;
		}
		if (s[i] == '$' && flagApici == 0)
		{
			return (0); //DA ESPANDERE
		}
		i++;
	}
	return (1); //NON VA ESPANSA
}


int	ft_is_there_an_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}


static void	ft_export_not_valid_var(void)
{
	exitStatus = 1;
	write(2, " not a valid identifier\n", 25);
}


static void	ft_export_valid_var(char **res)
{
	char	*tmp;

	tmp = ft_strtrim(res[1], "\"");
	if (ft_strlen(res[1]) > ft_strlen(tmp) || (tmp[0] >= '0' && tmp[0] <= '9'))
		setenv(res[0], tmp, 1);
	free (tmp);
}

void	ft_export_var(char *prompt)
{
	char	**res;

	if (prompt[0] == '=' && prompt[1] == '\0')
	{
		exitStatus = 1;
		write(2, "Error: not a valid identifier\n", 31);
		return;
	}
	res = ft_simple_split(prompt, '=');
	if (ft_is_valid_var_name(res[0]) == 1)
	{
		if (res[1] != 0)
			ft_export_valid_var(res);
		else
		{
			ft_free_strarr(res);
			free(res);
			return;
		}
	}
	else
		ft_export_not_valid_var();
	ft_free_strarr(res);
	free(res);
}///////////////////////////////COPIATA FINE

void	ft_clean_list(t_cmd *comandi)////////COPIATA
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

/////////////////////COPIATE



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
		waitpid(pid, &exitStatus, WNOHANG);
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




//////fine copiate
/////SIAMO ARRIVATI QUI









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
			printf("%s, infile = %d\n", tmp->full_cmd[i], tmp->infile);

			if (tmp->infile == 1025)
				printf("delimitatore %s\n", tmp->delimiter);
			i++;
		}
		i = 0;
		printf("CAMBIO\n");
		tmp = tmp->next;
	}
}

//ESEGUE ENV
void	ft_print_env_b()
{
	// char	**res;

	// res = __environ;
	// printf("qua ci sarebbe env ma su mac non funge\n"); //COMMENTATO PER MAC
	int	i;

	i = 0;
	while (__environ[i] != 0)
	{
		printf("%s\n", __environ[i]);
		i++;
	}
}

//UNSET VARIABILI

void	ft_unset_var(char *str)
{
	char	**arr;
	int		i;

	i = 1;
	arr = ft_split(str, ' ');
	// printf("unset %s\n", arr[1]);
	while (arr[i] != 0)
	{
		unsetenv(arr[i]);
		i++;
	}
	ft_free_strarr(arr);
	free(arr);
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
	int	flag;

	tmp = n;
	flag = 0;
	if (!to_print && n == 1)
		return;
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

//INTERCETTA CTRL + C E NON FA USCIRE DA MINISHELL

void	ft_signal_ctrl_c(int sig)
{
	(void)sig;
	if (sig != 0)
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

static void	ft_free_clean_exit(t_cmd *cmds, char **cmd_args)
{
	ft_clean_list(cmds);
	ft_free_strarr(cmd_args);
	free(cmd_args);
	exit(exitStatus);
}

static void	ft_others(char **cmd_args, t_prg box, char **envp)
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
		if (exitStatus == 1)
			flagexit = 1;
		waitpid(pid, &exitStatus, 0);
		if (flagexit == 1)
			exitStatus = 1;
	}
}

static void	ft_cd(char **cmd_args)
{
	if (cmd_args[2] == 0)
	{
		if(chdir(cmd_args[1]) == -1)
		{
			write(2, "no such file or directory\n", 27);
			exitStatus = 1;
		}
		else
			exitStatus = 0;
	}
	else
	{
		write(2, " too many arguments\n", 20);
		exitStatus = 1;
	}
	ft_free_strarr(cmd_args);
	free(cmd_args);
}


static void	ft_exit(char **cmd_args, t_prg box)
{
	char	*tmp;

	if (cmd_args[1] == 0)
		ft_free_clean_exit(box.cmds, cmd_args);
	else if (cmd_args[1] != 0 && cmd_args[2] == 0)
	{
		tmp = ft_remove_virgo_exit_status(cmd_args[1]);
		if (ft_is_good_exit_status(tmp) == 0)
			exitStatus = atoi(tmp);
		else
		{
			write(2, "wrong exit status\n", 19);
			exitStatus = 2;
		}
		ft_free_clean_exit(box.cmds, cmd_args);
	}
	else if (cmd_args[2] != 0)
	{
		write (2, "exit: too many arguments\n", 26);
		exitStatus = 1;
		ft_free_strarr(cmd_args);
		free(cmd_args);
	}
}

static void	ft_main_part_3(char **cmd_args, t_prg box, char **envp)
{
	if (!cmd_args[0])
		rl_redisplay();
	else if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
		ft_exit(cmd_args, box);
	else if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		ft_cd(cmd_args);
	else
		ft_others(cmd_args, box, envp);
}

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

static void	ft_do_everything(char *shell_prompt, char **envp)
{
	char	**cmd_args;
	t_prg	box;

	box.cmds = NULL;
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
}

int	main(int argc, char **argv, char **envp)
{
	char	*shell_prompt;
	char	*tmp;

	(void)argc;
	(void)argv;
	exitStatus = 0;
	shell_prompt = "@sovietshell: \033[0;37m";
	tmp = ft_strjoin("\033[1;31m", getenv("LOGNAME"));
	shell_prompt = ft_strjoin(tmp, shell_prompt);
	ft_do_everything(shell_prompt, envp);
	exit (exitStatus);
}
