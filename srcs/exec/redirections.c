/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:02 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/24 17:27:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * Gère les redirections de sortie (fichier avec ou sans append).
 * Retourne le descripteur de fichier ou -1 en cas d'erreur.
 */
int	handle_output_redir(t_redir *redir, int fd_out)
{
	if (fd_out != -2)
		close(fd_out);
	if (redir->token == GREATER) // '>' redirection
	{
		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(redir->file);
			return (-1);
		}
	}
	else if (redir->token == D_GREATER) // '>>' append redirection
	{
		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
		{
			perror(redir->file);
			return (-1);
		}
	}
	return (fd_out);
}

/**
 * Gère les redirections d'entrée (fichier ou heredoc).
 * Retourne le descripteur de fichier ou -1 en cas d'erreur.
 */
int	handle_input_redir(t_redir *redir, int fd_in, t_shell *shell)
{
	if (fd_in != -2)
		close(fd_in);
	if (redir->token == LOWER)  // '<' redirection
	{
		fd_in = open(redir->file, O_RDONLY);
		if (fd_in == -1)
		{
			perror(redir->file);
			return (-1);
		}
	}
	else if (redir->token == D_LOWER)  // '<<' heredoc
	{
		fd_in = handle_heredoc(redir->file, shell);
		if (fd_in == -1)
		{
			perror("heredoc.tmp");
			return (-1);
		}
	}
	return (fd_in);
}

/**

	* Applique toutes les redirections d'une commande à l'aide des fonctions de gestion des fds.
 * Retourne -1 en cas d'erreur,
	sinon les descripteurs de fichier sont mis à jour.
 */
void	apply_redirections(t_cmd *cmd, int *fd_in, int *fd_out, t_shell *shell)
{
	t_redir *redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->token == LOWER || redir->token == D_LOWER)
		{
			*fd_in = handle_input_redir(redir, *fd_in, shell);
		}
		else if (redir->token == GREATER || redir->token == D_GREATER)
		{
			*fd_out = handle_output_redir(redir, *fd_out);
		}
		if (*fd_in == -1 || *fd_out == -1)
			break ;
		redir = redir->next;
	}
}