/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:54:16 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/25 16:19:33 by jpointil         ###   ########.fr       */
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
