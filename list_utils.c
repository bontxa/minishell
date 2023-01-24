/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:07:52 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/24 13:13:49 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (prompt[start] != 0 && prompt[start][0] != '|'
		&& prompt[start][0] != '>')
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
	elem->outfile = 1;
	elem->next = NULL;
	return (elem);
}

static void	ft_add_element_3(char **cmd_arr, t_cmd *cmd_list, int *start)
{
	int		fd;
	t_cmd	*tmp;

	if (cmd_arr[*start][1] == '>')
	{
		*start = *start + 1;
		fd = open(cmd_arr[*start], O_APPEND | O_CREAT | O_RDWR, 0000644);
	}
	else
	{
		*start = *start + 1;
		fd = open(cmd_arr[*start], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	}
	tmp = cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->outfile = fd;
}

static void	ft_add_element_2(char **cmd_arr, t_cmd *cmd_list, int *start)
{
	t_cmd	*tmp;

	*start = *start + 1;
	tmp = cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_elem(cmd_arr, *start);
}

void	ft_add_element(t_cmd **cmd_list, char **cmd_arr)
{
	int		start;

	start = 0;
	if (*cmd_list == NULL)
		*cmd_list = create_elem(cmd_arr, 0);
	while (cmd_arr[start] != 0)
	{
		while (cmd_arr[start] != 0 && cmd_arr[start][0] != '|'
			&& cmd_arr[start][0] != '>')
			start++;
		if (cmd_arr[start] != 0 && cmd_arr[start][0] == '|')
			ft_add_element_2(cmd_arr, *cmd_list, &start);
		else if (cmd_arr[start] != 0 && cmd_arr[start][0] == '>')
			ft_add_element_3(cmd_arr, *cmd_list, &start);
	}
}
