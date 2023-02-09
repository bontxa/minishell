/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:07:22 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/09 12:39:01 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_if_trimmable(char *s1, size_t *first, size_t *last)
{
	if (s1[*first] == '\0')
	{
		*first = 0;
		*last = 0;
	}
}

int	ft_is_var_inside_quotes(char *s)
{
	int	i;
	int	flagapici;

	flagapici = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == 39)
		{
			if (flagapici == 1)
				flagapici = 0;
			else
				flagapici = 1;
		}
		if (s[i] == '$' && flagapici == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static void	ft_export_not_valid_var(void)
{
	g_exitstatus = 1;
	write(2, " not a valid identifier\n", 25);
}

static void	ft_export_valid_var(char **res)
{
	char	*tmp;

	tmp = ft_strtrim(res[1], "\"");
	if (ft_strlen(res[1]) > ft_strlen(tmp) || (tmp[0] >= '0' && tmp[0] <= '9'))
		setenv(res[0], tmp, 1);
	free (tmp);
}

void	ft_export_var(char *prompt)
{
	char	**res;

	if (prompt[0] == '=' && prompt[1] == '\0')
	{
		g_exitstatus = 1;
		write(2, "Error: not a valid identifier\n", 31);
		return ;
	}
	res = ft_simple_split(prompt, '=');
	if (ft_is_valid_var_name(res[0]) == 1)
	{
		if (res[1] != 0)
			ft_export_valid_var(res);
		else
		{
			ft_free_strarr(res);
			free(res);
			return ;
		}
	}
	else
		ft_export_not_valid_var();
	ft_free_strarr(res);
	free(res);
}
