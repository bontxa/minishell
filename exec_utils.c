#include "minishell.h"

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

void	execute_cmd(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**cmd_args;
	char	**cmd_paths;

	i = 0;
	cmd_args = ft_split(cmd, ' ');
	if (access(cmd, F_OK) == 0)
		execve(cmd, cmd_args, envp);
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
		printf("error");
		exit(-1);
	}
	else
		execve(cmd_paths[i], cmd_args, envp);
}
