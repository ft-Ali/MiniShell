/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:42:42 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/20 15:14:51 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_fds(t_fd *fds)
{
	fds->output = -2;
	fds->pipes[0] = -2;
	fds->pipes[1] = -2;
	fds->redir[0] = -2;
	fds->redir[1] = -2;
}

/**
 * Ajuste les descripteurs de fichiers selon les redirections et les pipes.
 * Les pipes sont fermés si les redirections prennent le dessus.
 */
void	set_fds(t_fd *fd)
{
	if (fd->pipes[1] != -2)
		fd->output = fd->pipes[1];
	if (fd->redir[0] != -2)
	{
		if (fd->input != -2)
			close(fd->input);
		fd->input = fd->redir[0];
	}
	if (fd->redir[1] != -2)
	{
		if (fd->pipes[1] != -2)
			close(fd->pipes[1]);
		fd->output = fd->redir[1];
	}
}

void	close_all_fds(t_fd *fds)
{
	if (!(fds->pipes[0] == -2) && fds->pipes[0] >= 0)
		close(fds->pipes[0]);
	if (!(fds->pipes[1] == -2) && fds->pipes[1] >= 0)
		close(fds->pipes[1]);
	if (!(fds->redir[0] == -2) && fds->redir[0] >= 0)
		close(fds->redir[0]);
	if (!(fds->redir[1] == -2) && fds->redir[1] >= 0)
		close(fds->redir[1]);
	if (!(fds->output == -2) && fds->output >= 0)
		close(fds->output);
	if (!(fds->input == -2) && fds->input >= 0)
		close(fds->input);
}

void	close_fds_parent(t_fd *fds)
{
	if (fds->input != -2 && fds->input >= 0)
		close(fds->input);
	if (fds->output != -2 && fds->output >= 0)
		close(fds->output);
}

// Exécuter une liste de commandes en boucle avec gestion des redirections et des erreurs
void	wait_child(t_shell *shell)
{
	int status;
	pid_t pid;

	// Attendre que tous les processus enfants se terminent
	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
		{
			shell->excode = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			shell->excode = 128 + WTERMSIG(status);
		}
	}
	if (pid == -1 && errno != ECHILD)
	{
		perror("wait");
		exit(EXIT_FAILURE);
	}
}