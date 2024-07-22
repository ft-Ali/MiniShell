/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/22 10:14:24 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}
