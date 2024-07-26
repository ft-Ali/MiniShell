/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:18:01 by jules             #+#    #+#             */
/*   Updated: 2024/07/26 14:45:36 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void    print_parser(t_cmd *cmd)
{
    int     i;

    if (!cmd)
    {
        printf("PKO\n");
        return ;
    }
    while (cmd)
    {
        printf("POK\n");
        if (cmd->commands)
        {
            printf("POK2\n");
            i = -1;
            while (cmd->commands[++i])
                printf("cmd : %s\n", cmd->commands[i]);
        }
        if (cmd->redir)
        {
            printf("POK3\n");
            while (cmd->redir)
            {
                printf("token : %d, file : %s\n", cmd->redir->token, cmd->redir->file);
                cmd->redir = cmd->redir->next;
            }
        }
        printf("POK4\n");
        cmd = cmd->next;
    }
}