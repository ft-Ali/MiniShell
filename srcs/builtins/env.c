/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:12:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 16:20:12 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_env(t_shell *shell, t_cmd *cmd, int output, t_fd *fds)
{
	char	**envp;
	int		i;

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
		ft_putstr_fd(envp[i++], output);
		ft_putstr_fd("\n", output);
	}
	free_envp(envp);
	free_shell(shell);
	close_all_fds(fds);
	exit(0);
}
