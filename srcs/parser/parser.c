/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/22 13:47:21 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir *void add_redir_node(t_token token, char *file)
{
	t_redir	*redir;

	redir = NULL;
	redir = ft_calloc(sizeof(t_redir));
	if (!redir)
		perror();
	redir->file = ft_strdup(file);
	redir->token = token;
	redir->next = NULL;
}

void	add_cmd_node(t_cmd *cmd, char **, char flag)
{
	// oui
}

t_cmd	*rec_parse(t_lex *lex, t_cmd *prev, t_cmd *cmd, int i)
{
	if (!lex)
		return (cmd);
	cmd = ft_calloc(sizeof(t_cmd));
	if (!cmd)
		// error
		cmd->prev = prev;
	while (lex)
	{
		if (lex->token == WORD)
		{
			cmd->commands[i] = ft_strdup(lexer->word);
			if (!cmd->commands[i])
				// secu
				i++;
		}
		else if (lex->token == PIPE)
		{
			cmd->commands[i] = NULL;
			cmd->next = rec_parse(lex->next, cmd, NULL, 0);
		}
		else
		{
			cmd->redir = add_redir_node(lex->token, lex->next->word);
			lex = lex->next;
			cmd->redir = cmd->redir->next;
		}
		lex = lex->next;
	}
	cmd->next = NULL;
	cmd->command[i] = NULL;
}
void	parser(t_shell *shell, t_lex *lex)
{
	shell.cmd = rec_parse(lex, NULL, NULL, 0);
	// free(lex);
}