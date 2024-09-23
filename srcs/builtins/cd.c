/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:12:28 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 16:38:56 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dir_check(t_shell *shell, t_cmd *cmd)
{
	DIR	*dir;

	dir = opendir(cmd->commands[1]);
	if (!dir)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->commands[1], 2);
		perror(NULL); // Affiche le message d'erreur système
		shell->excode = 1;
		return (0);
	}
	closedir(dir);
	return (1);
}

void	update_env(t_env *env, const char *key, char *new_value)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strictcmp(current->key, key))
		{
			free(current->value);
			if (new_value)
				current->value = ft_strdup(new_value);
			else
				current->value = NULL;
			return ;
		}
		current = current->next;
	}
}

void	update_pwd(t_shell *shell, char *old_pwd)
{
	t_env	*env_copy;

	env_copy = shell->env;
	update_env(env_copy, "OLDPWD", old_pwd);
	update_env(env_copy, "PWD", getcwd(NULL, 0));
	free(old_pwd);
}

void	exec_cd(t_shell *shell, char *dir)
{
	char	*old_pwd;
	t_env	*env_copy;

	env_copy = shell->env;
	// Cherche la valeur actuelle de PWD
	while (env_copy)
	{
		if (ft_strictcmp(env_copy->key, "PWD"))
		{
			old_pwd = ft_strdup(env_copy->value);
			break ;
		}
		env_copy = env_copy->next;
	}
	if (chdir(dir) == -1)
	{
		perror("minishell: cd");
		shell->excode = 1;
		free(old_pwd); // Nettoie old_pwd en cas d'échec de chdir
		return ;
	}
	update_pwd(shell, old_pwd);
}

void	cd_home(t_shell *shell)
{
	t_env	*env_copy;

	env_copy = shell->env;
	// Recherche de la variable HOME
	while (env_copy)
	{
		if (ft_strictcmp(env_copy->key, "HOME"))
			break ;
		env_copy = env_copy->next;
	}
	if (!env_copy || !env_copy->value)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->excode = 1;
		return ;
	}
	exec_cd(shell, env_copy->value);
}

void	bi_cd(t_shell *shell, t_cmd *cmd)
{
	printf("cd ok\n");
	if (cmd->commands[1] && cmd->commands[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->excode = 1;
		return ;
	}
	// Si aucun argument n'est fourni, on va dans $HOME
	if (!cmd->commands[1])
		cd_home(shell);
	else
	{
		// Vérifie la validité du répertoire avant de changer
		if (!dir_check(shell, cmd))
			return ;
		exec_cd(shell, cmd->commands[1]);
	}
}
