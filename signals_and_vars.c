/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_and_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:04:24 by aboncine          #+#    #+#             */
/*   Updated: 2023/02/08 17:29:52 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_strarr(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i])
	{
		free(strarr[i]);
		i++;
	}
}

void	free_n_exit(char *res)
{
	free(res);
	exit(0);
}

void	ft_unset_var(char *str)
{
	char	**arr;
	int		i;

	i = 1;
	arr = ft_split(str, ' ');
	while (arr[i] != 0)
	{
		unsetenv(arr[i]);
		i++;
	}
	ft_free_strarr(arr);
	free(arr);
}

void	ft_signal_ctrl_c(int sig)
{
	(void)sig;
	if (sig != 0)
		printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_ctrl_bs(int sig)
{
	(void)sig;
	return ;
}
