/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:58:50 by jules             #+#    #+#             */
/*   Updated: 2024/09/25 14:32:44 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_redir(redir->next);
	free(redir);
}

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
	if(cmd->cmd_path)
		free(cmd->cmd_path);
	free(cmd);
}
void free_loop(t_shell *shell)
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
	// if (lex->token)
	// 	free(lex->token.D_GREATER);
	if (lex->next)
		free_lex(lex->next);
	free(lex);
}
