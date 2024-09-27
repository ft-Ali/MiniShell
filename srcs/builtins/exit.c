/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:05:50 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/27 17:28:39 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_options(t_cmd *cmd, int *flag)
{
	int	i;

	i = 0;
	if (cmd->commands[1][i] == '+' || cmd->commands[1][i] == '-')
		i++;
	while (cmd->commands[1][i])
	{
		if (!ft_isdigit(cmd->commands[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->commands[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			(*flag) = 1;
			return (2);
		}
		i++;
	}
	return (ft_atoi(cmd->commands[1]) % 256);
}

void	bi_exit(t_shell *shell, t_cmd *cmd)
{
	int	ext;
	int	flag;

	flag = 0;
	if (cmd->commands[1])
		shell->tmpexcode = exit_options(cmd, &flag);
	if (cmd->commands[1] && cmd->commands[2] && !flag)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_putstr_fd("exit\n", 1);
		shell->excode = 1;
		shell->tmpexcode = 1;
		return ;
	}
	if (cmd->next || cmd->prev)
		return ;
	ext = shell->tmpexcode;
	free_shell(shell);
	ft_putstr_fd("exit\n", 1);
	exit(ext);
}
