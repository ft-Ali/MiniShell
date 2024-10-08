/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:12:28 by jules             #+#    #+#             */
/*   Updated: 2024/10/03 14:15:01 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	char	*pwdd;

	pwdd = getcwd(NULL, 0);
	env_copy = shell->env;
	update_env(env_copy, "OLDPWD", old_pwd);
	update_env(env_copy, "PWD", pwdd);
	free(old_pwd);
	free(pwdd);
}

void	exec_cd(t_shell *shell, char *dir, char *old_pwd)
{
	t_env	*env_copy;

	old_pwd = ft_strdup("");
	env_copy = shell->env;
	while (env_copy)
	{
		if (ft_strictcmp(env_copy->key, "PWD"))
		{
			if (env_copy->value)
			{
				free(old_pwd);
				old_pwd = ft_strdup(env_copy->value);
				break ;
			}
		}
		env_copy = env_copy->next;
	}
	if (chdir(dir) == -1)
	{
		perror("minishell: cd");
		shell->excode = 1;
		free(old_pwd);
		return ;
	}
	update_pwd(shell, old_pwd);
}

void	cd_home(t_shell *shell)
{
	t_env	*env_copy;

	env_copy = shell->env;
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
	exec_cd(shell, env_copy->value, NULL);
}

void	bi_cd(t_shell *shell, t_cmd *cmd)
{
	if (cmd->commands[1] && cmd->commands[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->excode = 1;
		return ;
	}
	if (!cmd->commands[1])
		cd_home(shell);
	else
	{
		if (!dir_check(shell, cmd))
			return ;
		exec_cd(shell, cmd->commands[1], NULL);
	}
}
