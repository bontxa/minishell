/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboncine <aboncine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:53:16 by ltombell          #+#    #+#             */
/*   Updated: 2023/03/10 13:03:18 by aboncine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_joiner(char *s1, char *s2)
{
	int		i;
	int		b;
	char	*ns;

	i = 0;
	b = 0;
	ns = (char *)malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1));
	if (!ns)
		return (NULL);
	while (s1[i])
		ns[b++] = s1[i++];
	i = 0;
	while (s2[i])
		ns[b++] = s2[i++];
	ns[b] = '\0';
	return (ns);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*newstr;

	if (s1 == NULL)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (s2 == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	if (s1[0] == '\0' && s2[0] == '\0')
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	newstr = ft_joiner(s1, s2);
	free(s1);
	free(s2);
	return (newstr);
}

char	*ft_freenreturn(char *str)
{
	free(str);
	return (NULL);
}
