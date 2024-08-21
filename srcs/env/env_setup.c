/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:17:44 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/21 14:30:55 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_env_key_value(t_shell *shell, t_env *new, char **envp, int i)
{
	char	*equal_sign;
	int		key_length;
	int		value_length;

	equal_sign = NULL;
	if (envp && envp[i])
		equal_sign = ft_strchr(envp[i], '=');
	else if (!equal_sign)
		exit_shell(shell, "Error: malloc failed env");
	key_length = equal_sign - envp[i];
	value_length = ft_strlen(equal_sign + 1);
	new->key = ft_calloc(key_length + 1, sizeof(char));
	if (!new->key)
		exit_shell(shell, "Error: malloc failed env");
	new->value = ft_calloc(value_length + 1, sizeof(char));
	if (!new->value)
	{
		free(new->key);
		exit_shell(shell, "Error: malloc failed env_value");
	}
	ft_strncpy(new->key, envp[i], key_length);
	ft_strncpy(new->value, equal_sign + 1, value_length);
}

static void	initialize_shell_level(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*current_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_shell(shell, "Error: malloc failed initialize_shell_level");
	new_entry->index = 2;
	new_entry->key = ft_strdup("SHLVL");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed initialize_shell_level");
	new_entry->value = ft_strdup("0");
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed initialize_shell_level");
	current_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = current_entry;
}

static void	initialize_underscore(t_shell *shell)
{
	t_env	*new_entry;
	t_env	*current_entry;

	current_entry = shell->env;
	while (current_entry->next)
		current_entry = current_entry->next;
	new_entry = ft_calloc(1, sizeof(t_env));
	if (!new_entry)
		exit_shell(shell, "Error: malloc failed initialize_underscore");
	new_entry->index = 3;
	new_entry->key = ft_strdup("_");
	if (!new_entry->key)
		exit_shell(shell, "Error: malloc failed initialize_underscore");
	new_entry->value = ft_strdup("./minishell");
	if (!new_entry->value)
		exit_shell(shell, "Error: malloc failed initialize_underscore");
	current_entry->next = new_entry;
	new_entry->next = NULL;
	new_entry->prev = current_entry;
}
// Gestion de l'absence de variables d'environnement
void	handle_empty_environment(t_shell *shell)
{
	initialize_current_directory(shell);
	initialize_shell_level(shell);
	initialize_underscore(shell);
	initialize_oldpwd(shell);
}