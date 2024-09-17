/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:17:44 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/17 17:09:54 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Set the key and value for an environment variable from envp array
void	set_env_vars(t_shell *shell, t_env *entry, char **envp, int index)
{
	char	*delimiter;
	int		key_len;
	int		value_len;

	if (!envp || !envp[index])
		exit_shell(shell, "Error: invalid environment variable format");
	delimiter = ft_strchr(envp[index], '=');
	if (!delimiter)
		exit_shell(shell, "Error: missing '=' in environment variable");
	key_len = delimiter - envp[index];
	value_len = ft_strlen(delimiter + 1);
	entry->key = ft_calloc(key_len + 1, sizeof(char));
	if (!entry->key)
		exit_shell(shell, "Error: malloc failed set_env_vars");
	entry->value = ft_calloc(value_len + 1, sizeof(char));
	if (!entry->value)
	{
		free(entry->key);
		exit_shell(shell, "Error: malloc failed set_env_vars");
	}
	ft_strncpy(entry->key, envp[index], key_len);
	ft_strncpy(entry->value, delimiter + 1, value_len);
}

// Add SHLVL environment variable
static void	add_shell_level(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*last_entry;

	last_entry = shell->env;
	while (last_entry->next)
		last_entry = last_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_shell(shell, "Error: malloc failed add_shell_level");
	new_entry->index = 2;
	new_entry->key = ft_strdup("SHLVL");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed add_shell_level");
	new_entry->value = ft_strdup("1");
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed add_shell_level");
	last_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = last_entry;
}

// Add underscore environment variable
static void	add_underscore(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*last_entry;

	last_entry = shell->env;
	while (last_entry->next)
		last_entry = last_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_shell(shell, "Error: malloc failed add_underscore");
	new_entry->index = 3;
	new_entry->key = ft_strdup("_");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed add_underscore");
	new_entry->value = ft_strdup("./minishell");
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed add_underscore");
	last_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = last_entry;
}

// Handle the case where no environment variables are provided
void	handle_no_env_vars(t_shell *shell)
{
	create_pwd(shell);
	add_shell_level(shell);
	add_underscore(shell);
	create_oldpwd(shell);
}
