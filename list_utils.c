/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltombell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:07:52 by aboncine          #+#    #+#             */
/*   Updated: 2023/01/24 15:16:50 by ltombell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_remove_from_arr(char **full_cmd, int i)
{
	int	b;
	char **res;

	b = 0;
	i++;
	while (full_cmd[b] != 0)
		b++;
	res = malloc(sizeof(char *) * (b - i + 1));
	b = 0;
	while (full_cmd[i] != 0)
		res[b++] = ft_strdup(full_cmd[i++]);
	res[b] = 0;
	return (res);
}

void	ft_check_for_minus(t_cmd *elem)
{
	int	i;

	i = 0;
	while (elem->full_cmd[i] != 0)
	{
		if (elem->full_cmd[i][0] == '<')
		{
			if (elem->full_cmd[i][1] && elem->full_cmd[i][1] == '<')
			{
				elem->infile = 1025;
				elem->delimiter = ft_strdup(elem->full_cmd[i + 1]);
				elem->full_cmd = ft_remove_from_arr(elem->full_cmd, i +1);
			}
			else
			{
				if (elem->full_cmd[i - 1])
				{
					elem->infile = open(elem->full_cmd[i - 1], O_RDONLY);
					if (elem->infile < 0)
						printf("unable to open file\n");
				}
				else
				{
					printf("errore nell'infile, parametro scorretto");
					exit(-1);
				}
				elem->full_cmd = ft_remove_from_arr(elem->full_cmd, i);
			}
		}
		i++;
	}
}

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
	ft_check_for_minus(elem);
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
