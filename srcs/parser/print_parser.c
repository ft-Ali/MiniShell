/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:18:01 by jules             #+#    #+#             */
/*   Updated: 2024/07/29 17:11:16 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

void print_parser(t_cmd *cmd)
{
    int i;

    if (!cmd)
    {
        printf("No commands found\n");
        return;
    }

    while (cmd)
    {
        printf("Command found\n");
        
        // Print commands
        if (cmd->commands)
        {
            printf("Commands:\n");
            i = -1;
            while (cmd->commands[++i])
                printf("cmd: %s\n", cmd->commands[i]);
        }

        // Print redirections
        if (cmd->redir)
        {
            printf("Redirections:\n");
            while (cmd->redir)
            {
                printf("token: %d, file: %s\n", cmd->redir->token, cmd->redir->file);
                cmd->redir = cmd->redir->next;
            }
        }

        cmd = cmd->next;
    }
}

