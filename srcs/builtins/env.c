/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:12:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/19 18:02:45 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_env(t_shell *shell, t_cmd *cmd)
{
	int i;
	char **envp;

	if (cmd->commands[1])
	{
		exit_shell(shell, "minishell: env: too many arguments\n");
		free_shell(shell);
		exit(127);
	}
	i = 0;
	envp = env_list_to_envp(shell->env);
	while (envp[i])
	{
		//printf(" value : %s, key  : %s", shell->env->value[i], shell->env->key[i]);
		ft_putstr_fd(envp[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	free_shell(shell);
	exit(0);
}