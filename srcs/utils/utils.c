/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:42:09 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 17:49:13 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_end_index(const char *s1, const char *s2, int i)
{
	char *pos = strstr(s2, s1);
	if (pos)
		return ((pos - s2) + strlen(s1) - 1);
	return (i);
}

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;

	if (!s2[0])
		return ((char *)s1);
	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] && s2[j] && s1[i + j] == s2[j])
			j++;
		if (!s2[j])
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s);
	result = (char *)malloc(len + 2);
	if (!result)
	{
		free(s);
		return (NULL);
	}
	ft_strcpy(result, s);
	result[len] = c;
	result[len + 1] = '\0';
	free(s);
	return (result);
}
