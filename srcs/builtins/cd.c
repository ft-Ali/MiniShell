/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:12:28 by jules             #+#    #+#             */
/*   Updated: 2024/09/18 11:59:55 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_check(t_shell *shell, t_cmd *cmd)
{
	DIR	*dir;

	dir = opendir(cmd->tab[1]);
	if (!dir)
	{
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(cmd->tab[1], 2);
		perror(NULL);
		shell->excode = 1;
		return (0);
	}
	closedir(dir);
	return (1);
}

void    bi_cd(t_shell *shell, t_cmd *cmd)
{
    if (cmd->commands[1] && cmd->commands[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->excode = 1;
		return ;
	}
    if (cmd->commands[1])
		if (!dir_check(shell, cmd))
			return ;
	if (cmd->next || cmd->prev)
		return ;
	if (!cmd->commands[1])
		ft_cdhome(shell);
	else
		ft_cdexec(shell, cmd->commands[1]);
}