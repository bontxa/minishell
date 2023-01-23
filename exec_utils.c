#include "minishell.h"

int		is_there_a_pipe(char *s)
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

int		check_for_pipes(char **s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		if (is_there_a_pipe(s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

char	**get_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**res;

	i = 0;
	while (envp[i][0] != 'P' || envp[i][1] != 'A' || envp[i][2] != 'T')
	{
		i++;
	}
	tmp = ft_strtrim(envp[i], "PATH=");
	res = ft_split(tmp, ':');
	free(tmp);
	return (res);
}

void	execute_cmd(char **cmd_args, char **envp)
{
	int		i;
	char	*tmp;
	char	*cmd;
	char	**cmd_paths;
	char	cwd[1024];

	i = 0;
	if (ft_strncmp(cmd_args[0], "pwd", 3) == 0)
	{
		getcwd(cwd, sizeof(cwd));
		printf("%s\n", cwd);
		exit(0);
	}
	else if (ft_strncmp(cmd_args[0], "echo", 4) == 0)
	{
		if (!cmd_args[1])
			printf("\n");
		if (ft_strncmp(cmd_args[1], "-n", 2) == 0)
		{
			ft_simple_echo(cmd_args, 2);
			exit(0);
		}
		else
		{
			ft_simple_echo(cmd_args, 1);
			exit(0);
		}
		exit(0);
	}
	else {
		cmd = ft_strdup(cmd_args[0]);
		if (access(cmd_args[0], F_OK) == 0)
			execve(cmd_args[0], cmd_args, envp);
		cmd_paths = get_paths(envp);
		while (cmd_paths[i] != 0)
		{
			tmp = ft_strjoin(cmd_paths[i], "/");
			free (cmd_paths[i]);
			cmd_paths[i] = ft_strjoin(tmp, cmd_args[0]);
			free(tmp);
			if (access(cmd_paths[i], F_OK) == 0)
				break;
			i++;
		}
		if (cmd_paths[i] == 0)
		{
			printf("error\n");
			exit(-1);
		}
		else
		{
			execve(cmd_paths[i], cmd_args, envp);
		}
	}
}
