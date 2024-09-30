/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:42:09 by jules             #+#    #+#             */
/*   Updated: 2024/09/30 12:20:15 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_putstr_fd_e(char *s, int fd, t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	if (!s || !fd)
		return ;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			str = ft_itoa(shell->excode);
			ft_putstr_fd(str, fd);
			free(str);
			i += 2;
			break ;
		}
		write(fd, &s[i], 1);
		i++;
	}
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
