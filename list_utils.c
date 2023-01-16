#include "minishell.h"

static t_cmd	*create_elem(int char **strarr)
{
	t_cmd	*elem;

	elem = (t_cmd *)malloc(sizeof(t_cmd));
	elem->cmd = s
	elem->next = NULL;
	return (elem);
}

void	ft_add_element(t_cmd **cmd_list, char **cmd_arr)
{
	t_cmd	*new;
	t_cmd	*tmp;

	if (!*lista)
		*lista = create_elem(cmd_arr);
	else
	{
		tmp = *lista;
		while (tmp->next)
			tmp = tmp->next;
		new = create_elem(n);
		tmp->next = new;
	}
}
