#include "minishell.h"

int		how_many_special(char **prompt, char c)
{
	int	b;
	int	count;

	count = 0;
	b = 0;
	while(prompt[b] != 0)
	{
		if (prompt[b][0] == c)
			count++;
		b++;
	}
	return (count);
}

int		arr_len_before_s_c(char **prompt, int start)
{
	int	res;

	res = 0;
	while (prompt[start] != 0 && prompt[start][0] != '|')
	{
		res++;
		start++;
	}
	return (res);
}

void	create_cmd(char **prompt, t_cmd *cmd, int start)
{
	int	i;

	i = 0;
	cmd->full_cmd = (char **) malloc (sizeof(char *) * (arr_len_before_s_c(prompt, start)) + 1);
	while (prompt[start] != 0 && prompt[start][0] != '|')
	{
		cmd->full_cmd[i] = ft_strdup(prompt[start]);
		start++;
		i++;
	}
	cmd->full_cmd[i] = 0;
	i = 0;
	while (cmd->full_cmd[i] != 0)
	{
		printf("%s\n", cmd->full_cmd[i]);
		i++;
	}
}

void	populate_cmd(char **prompt, t_prg *box)
{
	int	b;
	int	flag;
	int	i;

	b = 0;
	i = 0;
	flag = 0;
	box->cmds = (t_cmd *) malloc(sizeof(t_cmd) * (how_many_special(prompt, '|') + 1));
	while (prompt[b] != 0)
	{
		if (flag == 0)
		{
			create_cmd(prompt, &box->cmds[i], b);
			flag = 1;
			b++;
			i++;
		}
		if (prompt[b][0] == '|')
		{
			flag = 0;
		}
		b++;
	}
}

int	main(int argc, char **argv)
{
	t_prg	box;

	populate_cmd(argv, &box);
}
