/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:12:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/26 15:59:57 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_env(t_shell *shell, t_cmd *cmd, int output, t_fd *fds)
{
	char	**envp;
	int		i;

	if (cmd->commands[1])
	{
		
		close_all_fds(fds);
		shell->excode = 127;
		exit_shell(shell, "minishell: env: too many arguments\n");
	}
	i = 0;
	envp = env_list_to_envp(shell->env, 0, 0);
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], output);
		ft_putstr_fd("\n", output);
	}
	free_envp(envp);
	free_shell(shell);
	close_all_fds(fds);
	exit(0);
}
