/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:30:48 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/23 12:40:23 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_env_entries(t_env *env_list)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**env_list_to_envp(t_env *env_list)
{
	int		size;
	char	**envp;
	t_env	*tmp;
	int		i;

	size = count_env_entries(env_list);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	tmp = env_list;
	i = 0;
	while (tmp)
	{
		if (!tmp->isunset)
		{
			envp[i] = ft_strjoin(tmp->key, "=");
			if (!envp[i])
				return (NULL);
			envp[i] = strjoin_free(envp[i], tmp->value);
			if (!envp[i])
				return (NULL);
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

