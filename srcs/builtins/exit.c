/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:05:50 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/16 16:54:50 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bt_exit(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
    int     ext;
    int     flag;

    shell->tmpextcode = exit_args(cmd, &flag);
    ext = shell->tmpextcode;
    free_shell(shell);
    ft_putstr_fd("exit\n", 1);
    exit(ext);
}