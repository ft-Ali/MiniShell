/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:58:02 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/18 15:04:40 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Gestion des redirections dans les commandes
void	handle_redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/**
 * Ouvre un fichier pour redirection de sortie avec ajout.
 */
void	handle_redirection_out_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

/**
 * Ouvre un fichier pour redirection d'entre.
 */
void	handle_redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

/**
 * Applique les redirections à la commande.
 */
void	apply_redirections(t_cmd *cmd)
{
	t_redir *redir = cmd->redir;

	while (redir)
	{
		if (redir->token == GREATER)
		{
			handle_redirection_out(redir->file);
		}
		else if (redir->token == D_GREATER)
		{
			handle_redirection_out_append(redir->file);
		}
		else if (redir->token == LOWER)
		{
			handle_redirection_in(redir->file);
		}
		else if (redir->token == D_LOWER)
		{
			handle_heredoc(redir->file);
		}
		redir = redir->next;
	}
}