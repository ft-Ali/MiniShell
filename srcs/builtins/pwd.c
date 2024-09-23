/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:28:49 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 10:12:33 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_pwd(t_shell *shell, t_cmd *cmd)
{
	char *pwd;

	//printf("pwd ok\n");
	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
    else if (cmd->commands[1] && cmd->commands[1][0] == '-')
	{
		ft_putstr_fd("minishell: pwd: invalid option", 2);
		free(pwd);
		free_shell(shell);
		exit(2);
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	free(pwd);
	free_shell(shell);
	exit(0);
}