#include "minishell.h"

// {
// 	char **cmd;
// 	int		infile;
// 	int		outfile;
// }
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
char	**copy_to_list(char **prompt, int start)
{
	int		b;
	char	**res;

	b = start;
	while (prompt[b] != 0 && prompt[b][0] != '|' )
		b++;
	printf("%d sono arrivato a\n", b);
	res = (char **) malloc (sizeof(char *) * (b - start + 1));
	b = 0;
	while (prompt[start] != 0 && prompt[start][0] != '|')
	{
		res[b] = ft_strdup(prompt[start]);
		start++;
		b++;
	}
	res[b] = 0;
	return (res);
}


static t_cmd	*create_elem(char **strarr, int start)
{
	t_cmd	*elem;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	elem->full_cmd = copy_to_list(strarr, start);
	elem->next = NULL;
	return (elem);
}

void	ft_add_element(t_cmd **cmd_list, char **cmd_arr)
{
	t_cmd	*tmp;
	int		start;

	start = 0;
	if (!cmd_list)
		*cmd_list = create_elem(cmd_arr, 0);
	while (cmd_arr[start])
	{
		while (cmd_arr[start][0] != '|' && cmd_arr[start])
			start++;
		if (cmd_arr[start][0] == '|')
		{
			start++;
			tmp = *cmd_list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = create_elem(cmd_arr, start);
		}
	}
	// else
	// {
	// 	tmp = *cmd_list;
	// 	while (tmp->next)
	// 		tmp = tmp->next;
	// 	tmp->next = create_elem(cmd_arr);
	// }
}

int		main(int argc, char **argv)
{
	char	**res;
	t_cmd	*cmd;

	// cmd = create_elem(argv, 0);
	// cmd->next = create_elem(argv, 6);
	ft_add_element(&cmd, argv);
	// int	i;
	// i = 0;
	// while (cmd->full_cmd[i] != 0)
	// {
	// 	printf("%s\n", cmd->full_cmd[i]);
	// 	i++;
	// }
	// cmd = cmd->next;
	// i = 0;
	// while (cmd->full_cmd[i] != 0)
	// {
	// 	printf("%s\n", cmd->full_cmd[i]);
	// 	i++;
	// }
}
