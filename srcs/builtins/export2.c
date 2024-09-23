/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:05:44 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/23 16:52:58 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_or_update_env(t_env **env, const char *key, const char *value,
		t_shell *shell)
{
	t_env	*temp;
	t_env	*new_node;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		exit_shell(shell, "Error: malloc failed");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	if (*env)
		(*env)->prev = new_node;
	*env = new_node;
    shell->env = *env;
}

void	trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	if (start != str)
	{
		while (*start)
			*str++ = *start++;
		*str = '\0';
	}
}

void	free_joined(char *str)
{
	if (str)
		free(str);
}
