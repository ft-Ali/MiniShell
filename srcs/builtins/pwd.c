/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:28:49 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 15:57:38 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	bi_pwd(t_shell *shell, t_cmd *cmd, int output, t_fd *fds)
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
		ft_putstr_fd(pwd, output);
		ft_putstr_fd("\n", output);
	}
	free(pwd);
	free_shell(shell);
	close_all_fds(fds);
	exit(0);
}