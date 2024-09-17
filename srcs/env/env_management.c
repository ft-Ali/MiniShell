/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:15:35 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/17 17:09:35 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Get the value associated with a given key from the environment list
char	*get_value_by_key(const char *key, t_env *env)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, key_len) == 0
			&& env->key[key_len] == '\0')
		{
			printf("Found key: %s\n", env->key);
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

// Load the environment list from the provided environment variables
void	load_env(t_shell *shell, char **env_vars)
{
	int		i;
	t_env	*node;

	i = 0;
	if (!env_vars || !env_vars[0])
	{
		handle_no_env_vars(shell);
		return ;
	}
	while (env_vars[i])
	{
		node = ft_calloc(1, sizeof(t_env));
		if (!node)
			exit_shell(shell, "Error: malloc failed load_environment");
		add_env_entry(shell, node, env_vars, i);
		i++;
	}
}

// Create the OLDPWD environment variable
void	create_oldpwd(t_shell *shell)
{
	t_env	*last_node;
	t_env	*new_node;

	last_node = shell->env;
	while (last_node->next)
		last_node = last_node->next;
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		exit_shell(shell, "Error: malloc failed create_oldpwd");
	new_node->key = ft_strdup("OLDPWD");
	if (!new_node->key)
		exit_shell(shell, "Error: malloc failed create_oldpwd");
	new_node->value = ft_strdup("OLDPWD");
	if (!new_node->value)
		exit_shell(shell, "Error: malloc failed create_oldpwd");
	new_node->index = 4;
	last_node->next = new_node;
	new_node->prev = last_node;
	new_node->next = NULL;
}

// Add a new environment entry to the list
void	add_env_entry(t_shell *shell, t_env *node, char **env_vars, int idx)
{
	t_env	*current;

	current = shell->env;
	node->index = idx;
	set_env_vars(shell, node, env_vars, idx);
	node->next = NULL;
	node->prev = NULL;
	if (!current)
		shell->env = node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = node;
		node->prev = current;
	}
}

// Create the PWD environment variable with the current directory
void	create_pwd(t_shell *shell)
{
	char	*current_dir;
	t_env	*node;

	node = ft_calloc(1, sizeof(t_env));
	current_dir = getcwd(NULL, 0);
	if (!node || !current_dir)
		exit_shell(shell, "Error: malloc failed create_pwd");
	node->index = 1;
	node->key = ft_strdup("PWD");
	if (!node->key)
		exit_shell(shell, "Error: malloc failed create_pwd");
	node->value = ft_strdup(current_dir);
	if (!node->value)
		exit_shell(shell, "Error: malloc failed create_pwd");
	node->prev = NULL;
	node->next = NULL;
	shell->env = node;
}
