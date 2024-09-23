/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:12:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 15:58:11 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_env(t_shell *shell, t_cmd *cmd, int output, t_fd *fds)
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
		ft_putstr_fd(envp[i++], output);
		ft_putstr_fd("\n", output);
	}
	free_envp(envp);
	free_shell(shell);
	close_all_fds(fds);
	exit(0);
}