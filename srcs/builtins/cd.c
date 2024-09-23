/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:12:28 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 15:40:20 by alsiavos         ###   ########.fr       */
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
		perror(NULL);
		shell->excode = 1;
		return (0);
	}
	closedir(dir);
	return (1);
}

void	update_pwd(t_shell *shell, char *tmp)
{
	while (shell->env)
	{
		if (ft_strictcmp(shell->env->key, "OLDPWD"))
		{
			free(shell->env->value);
			shell->env->value = ft_strdup(tmp);
		}
		if (ft_strictcmp(shell->env->key, "PWD"))
		{
			free(shell->env->value);
			shell->env->value = getcwd(NULL, 0);
		}
		shell->env = shell->env->next;
	}
	free(tmp);
}

void	exec_cd(t_shell *shell, char *dir)
{
	char	*tmp;

	while(shell->env)
	{
		if (ft_strictcmp(shell->env->key, "PWD"))
			tmp = ft_strdup(shell->env->value);
		shell->env = shell->env->next;
	}
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("chdir", 2);
		shell->excode = 1;
		return ;
	}
	update_pwd(shell, tmp);
	// uodate_env(shell, tmp);
	
}

void	cd_home(t_shell *shell)
{
	while (shell->env)
	{
		if (ft_strictcmp(shell->env->key, "HOME"))
			break ;
		if (!shell->env->next)
		{
			ft_putstr_fd("minihsell: cd: HOME not set\n", 2);
			shell->excode = 1;
			return ;
		}
		shell->env = shell->env->next;
	}
	exec_cd(shell, shell->env->value);
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
	if (cmd->commands[1])
		if (!dir_check(shell, cmd))
			return ;
	if (cmd->next || cmd->prev)
		return ;
	if (!cmd->commands[1])
		cd_home(shell);
	else
		exec_cd(shell, cmd->commands[1]);
}