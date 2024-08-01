/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:18:01 by jules             #+#    #+#             */
/*   Updated: 2024/08/01 16:45:16 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_parser(t_cmd *cmd)
{
	int		i;
	t_redir	*current_redir;

	if (!cmd)
	{
		printf("PKO\n");
		return ;
	}
	while (cmd)
	{
		if (cmd->commands)
		{
			printf("cmd: ");
			i = 0;
			while (cmd->commands[i])
			{
				printf("%s ", cmd->commands[i]);
				i++;
			}
			printf("\n");
		}
		if (cmd->redir)
		{
			printf("Redirections:\n");
			current_redir = cmd->redir;
			while (current_redir)
			{
				printf("token: %d, file: %s\n", current_redir->token,
					current_redir->file);
				current_redir = current_redir->next;
			}
		}
		cmd = cmd->next;
	}
}
