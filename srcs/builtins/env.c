/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:12:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/18 12:27:03 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_env(t_shell *shell, t_cmd *cmd)
{
	int i;

	if (cmd->commands[1])
	{
		exit_shell(shell, "minishell: env: too many arguments\n");
		free_shell(shell);
		exit(127);
	}
	i = 0;
	while (shell->env->value[i])
	{
		ft_putstr_fd(shell->env->value[i++], 1);
		ft_putstr_fd("\n", 1);
	}
	free_shell(shell);
	exit(0);
}