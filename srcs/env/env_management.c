/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:15:35 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/21 14:31:06 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*find_env_value(char *key, t_env *envp)
{
	int		len;
	t_env	*tmp_envp;

	tmp_envp = envp;
	len = ft_strlen(key);
	while (tmp_envp)
	{
		if (!ft_strncmp(key, tmp_envp->key, len) && tmp_envp->key[len] == '\0')
			return (tmp_envp->value);
		tmp_envp = tmp_envp->next;
	}
	return (NULL);
}

void	get_environment(t_shell *shell, char **envp)
{
	int		index;
	t_env	*new_env_node;

	index = 0;
	if (!envp || !envp[0])
	{
		handle_empty_environment(shell);
		return ;
	}
	while (envp[index])
	{
		new_env_node = ft_calloc(1, sizeof(t_env));
		if (!new_env_node)
			exit_shell(shell, "Error: malloc failed get_environment");
		update_env_node(shell, new_env_node, envp, index);
		index++;
	}
}

void	initialize_oldpwd(t_shell *shell)
{
	t_env	*current_entry;
	t_env	*new_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_shell(shell, "Error: malloc failed initialize_oldpwd");
	new_entry->key = ft_strdup("OLDPWD");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed initialize_oldpwd");
	new_entry->value = ft_strdup("OLDPWD");
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed initialize_oldpwd");
	new_entry->index = 4;
	current_entry->next = new_entry;
	new_entry->prev = current_entry;
	new_entry->next = NULL;
}
void	update_env_node(t_shell *shell, t_env *new_env_node, char **envp,
		int index)
{
	t_env	*current;

	current = shell->env;
	new_env_node->index = index;
	set_env_key_value(shell, new_env_node, envp, index);
	new_env_node->next = NULL;
	new_env_node->prev = NULL;
	if (!current)
		shell->env = new_env_node;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_env_node;
		new_env_node->prev = current;
	}
}

void	initialize_current_directory(t_shell *shell)
{
	char	*current_directory;
	t_env	*new_entry;

	new_entry = ft_calloc(1, sizeof(t_env));
	current_directory = getcwd(NULL, 0);
	if (!new_entry || !current_directory)
		exit_shell(shell, "Error: malloc failed initialize_current_directory");
	new_entry->index = 1;
	new_entry->key = ft_strdup("PWD");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed initialize_current_directory");
	new_entry->value = ft_strdup(current_directory);
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed initialize_current_directory");
	new_entry->prev = NULL;
	new_entry->next = NULL;
	shell->env = new_entry;
}
