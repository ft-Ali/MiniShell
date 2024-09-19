/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:42 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/19 11:30:08 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	newline_check(char **cmd, int *valid)
{
	int w;
	int c;

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

void bi_echo(t_shell *shell, t_cmd *cmd)
{
    int new_line;
    int i;

    (void)shell;
    new_line = 0;
    i = newline_check(cmd->commands, &new_line);
    if (cmd->commands[1])
    {
        while (cmd->commands[i])
        {
            if (cmd->commands[i] && !cmd->commands[i + 1])
                printf("%s", cmd->commands[i++]);
            else if (cmd->commands[i])
                printf("%s", cmd->commands[i++]);
        }
    }
    if (!new_line)
        printf("\n");
    return ;
    //exit_shell(shell);
}
