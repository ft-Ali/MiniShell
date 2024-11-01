/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 14:05:44 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/27 19:13:12 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*create_new_env(const char *key, const char *value, t_shell *shell)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		exit_shell(shell, "Error: malloc failed");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
		exit_shell(shell, "Error: malloc failed");
	return (new_node);
}

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
			(free(temp->value), temp->value = ft_strdup(value));
			if (!temp->value)
				exit_shell(shell, "Error: malloc failed");
			return ;
		}
		temp = temp->next;
	}
	new_node = create_new_env(key, value, shell);
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
