/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:28:49 by jules             #+#    #+#             */
/*   Updated: 2024/09/18 14:05:25 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(t_shell *shell, t_cmd *cmd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
    else if (cmd->tab[1] && cmd->tab[1][0] == '-')
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