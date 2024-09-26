/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:58:50 by jules             #+#    #+#             */
/*   Updated: 2024/09/26 14:13:11 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_exp(t_expand *expand)
{
	if (!expand)
		return ;
	if (expand->input)
		free(expand->input);
	if (expand->output)
		free(expand->output);
	free(expand);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->commands)
	{
		i = -1;
		while (cmd->commands[++i])
			free(cmd->commands[i]);
		free(cmd->commands);
	}
	if (cmd->redir)
		free_redir(cmd->redir);
	if (cmd->next)
		free_cmd(cmd->next);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	free(cmd);
}

void	free_loop(t_shell *shell)
{
	if (shell->lex)
		free_lex(shell->lex);
	if (shell->cmd)
		free_cmd(shell->cmd);
	shell->cmd = NULL;
	shell->lex = NULL;
}

void	free_path(t_path *path)
{
	if (!path)
		return ;
	if (path->path_str)
		free(path->path_str);
	if (path->next)
		free_path(path->next);
	free(path);
}

void	free_lex(t_lex *lex)
{
	if (!lex)
		return ;
	if (lex->word)
		free(lex->word);
	if (lex->next)
		free_lex(lex->next);
	free(lex);
}
