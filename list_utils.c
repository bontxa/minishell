#include "minishell.h"

char	**copy_to_list(char **prompt, int start)
{
	int		b;
	char	**res;

	b = start;
	while (prompt[b] != 0 && prompt[b][0] != '|' )
		b++;
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
	if (*cmd_list == NULL)
		*cmd_list = create_elem(cmd_arr, 0);
	while (cmd_arr[start] != 0)
	{
		while (cmd_arr[start] != 0 && cmd_arr[start][0] != '|')
			start++;
		if (cmd_arr[start] != 0 && cmd_arr[start][0] == '|')
		{
			start++;
			tmp = *cmd_list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = create_elem(cmd_arr, start);
		}
	}
}

// int		main()
// {
// 	char	**res;
// 	t_cmd	*cmd;

// 	char *ciccio[8];
// 	cmd = NULL;
// 	ciccio[0] = ft_strdup("echo");
// 	ciccio[1] = ft_strdup("hello     there");
// 	ciccio[2] = ft_strdup("how");
// 	ciccio[3] = ft_strdup("are");
// 	ciccio[4] = ft_strdup("|");
// 	ciccio[5] = ft_strdup("wc");
// 	ciccio[6] = ft_strdup("-l");
// 	ciccio[7] = 0;
// 	// cmd = create_elem(argv, 0);
// 	// cmd->next = create_elem(argv, 6);
// 	ft_add_element(&cmd, ciccio);
// 	int	i;
// 	i = 0;
// 	while (cmd->full_cmd[i] != 0)
// 	{
// 		printf("%s\n", cmd->full_cmd[i]);
// 		i++;
// 	}
// 	printf("cambio!\n");
// 	cmd = cmd->next;
// 	i = 0;
// 	while (cmd->full_cmd[i] != 0)
// 	{
// 		printf("%s\n", cmd->full_cmd[i]);
// 		i++;
// 	}
// }
