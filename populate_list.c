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
}

void	populate_cmd(char **prompt, t_prg *box)
{
	int	b;
	int	flag;

	b = 0;
	flag = 0;
	box->cmds = (t_list *) malloc(sizeof(t_list) * (how_many_special(prompt, '|') + 1));
	while (prompt[b] != 0)
	{
		if (flag == 0)
		{
			box->cmds->content =
		}
	}

}


//echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
// echo
// hello      there
// how
// are
// you
// doing?
// lapenji
// |
// wc
// -l
