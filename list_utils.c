#include "minishell.h"

char	**copy_to_list(char **prompt, int start)
{
	int		b;
	char	**res;

	b = start;
	while (prompt[b] != 0 && prompt[b][0] != '|' && prompt[b][0] != '>')
		b++;
	res = (char **) malloc (sizeof(char *) * (b - start + 1));
	b = 0;
	while (prompt[start] != 0 && prompt[start][0] != '|' && prompt[start][0] != '>')
	{
		res[b] = ft_strdup(prompt[start]);
		start++;
		b++;
	}
	res[b] = 0;
	// printf("%s\n", res[0]);
	return (res);
}


static t_cmd	*create_elem(char **strarr, int start)
{
	t_cmd	*elem;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	elem->full_cmd = copy_to_list(strarr, start);
	elem->outfile = 1;
	elem->next = NULL;
	return (elem);
}

void	ft_add_element(t_cmd **cmd_list, char **cmd_arr)
{
	t_cmd	*tmp;
	int		start;
	int		fd;

	start = 0;
	if (*cmd_list == NULL)
		*cmd_list = create_elem(cmd_arr, 0);
	while (cmd_arr[start] != 0)
	{
		while (cmd_arr[start] != 0 && cmd_arr[start][0] != '|' && cmd_arr[start][0] != '>')
			start++;
		if (cmd_arr[start] != 0 && cmd_arr[start][0] == '|')
		{
			start++;
			tmp = *cmd_list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = create_elem(cmd_arr, start);
		}
		else if (cmd_arr[start] != 0 && cmd_arr[start][0] == '>')
		{
			if (cmd_arr[start][1] == '>')
			{
				start++;
				fd = open(cmd_arr[start], O_APPEND | O_CREAT | O_RDWR, 0000644);
			}
			else
			{
				start++;
				fd = open(cmd_arr[start], O_TRUNC | O_CREAT | O_RDWR, 0000644);
			}

			tmp = *cmd_list;
			while (tmp->next)
				tmp = tmp->next;
			// printf("%d\n", fd);
			tmp->outfile = fd;
		}
	}
}
