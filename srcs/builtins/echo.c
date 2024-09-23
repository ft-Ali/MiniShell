/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:42 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/23 14:30:29 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	newline_check(char **cmd, int *valid)
{
	int	w;
	int	c;

	w = 1;
	while (cmd[w] && cmd[w][0] == '-' && cmd[w][1] == 'n')
	{
		c = 1;
		if (cmd[w][0] == '-' && cmd[w][1] == 'n')
		{
			while (cmd[w][c] == 'n')
				c++;
			if (cmd[w][c] != '\0')
				return (w);
		}
		*valid = 1;
		w++;
	}
	return (w);
}

void	bi_echo(t_shell *shell, t_cmd *cmd, int fd_out, t_fd *fd)
{
	int	new_line;
	int	i;

	(void)shell;
	// printf("echo ok\n");
	new_line = 0;
	i = newline_check(cmd->commands, &new_line);
	if (cmd->commands[1])
	{
		while (cmd->commands[i])
		{
			if (cmd->commands[i] && !cmd->commands[i + 1])
				ft_putstr_fd(cmd->commands[i], fd_out);
			else if (cmd->commands[i])
			{
				ft_putstr_fd(cmd->commands[i], fd_out);
				ft_putstr_fd(" ", fd_out);
			}
			i++;
		}
	}
	if (!new_line)
		ft_putstr_fd("\n", fd_out);
	(close_all_fds(fd), exit_shell(shell, ""));
	return ;
}
