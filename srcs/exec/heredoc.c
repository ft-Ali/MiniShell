/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:00:00 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/20 14:17:31 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fonction pour écrire dans le fichier temporaire pendant le heredoc.
void	loop_here_doc(char *delimiter, int fd) // rajoute de t_shell
{
	char *line;
	char *limiter;

	// Ajouter un saut de ligne au délimiteur (comme dans l'original)
	limiter = ft_strjoin(delimiter, "\n");
	while (1)
	{
		line = readline(RED "> " RESET); // Affichage du prompt heredoc
		// Gestion de l'interruption par Ctrl-C
		// if (g_signal == SIGINT)
		// {
		// 	shell->exit_code = 130;
		// 	g_signal = 0;
		// 	shell->skip_here = 1;
		// Indique qu'on doit ignorer la suite du heredoc
		// 	break ;
		// }
		// Si la ligne est égale au délimiteur, on termine la boucle
		if (line == NULL || (!ft_strncmp(line, limiter, ft_strlen(line))
				&& ft_strlen(line) == ft_strlen(limiter) - 1))
		{
			free(line);
			break ;
		}
		// Écriture dans le fichier du heredoc
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	free(limiter);
}

/**

	* Gère la redirection heredoc (<<) en créant un fichier temporaire et en écrivant dedans
 * jusqu'à rencontrer le délimiteur.
 */
int	handle_heredoc(char *delimiter)
{
	char	*file_name;
	int		fd_out;
	int		fd_in;

	file_name = ft_strdup("heredoc_tmp_");
	while (access(file_name, F_OK) == 0)
	file_name = strjoin_free(file_name, "42");
	fd_out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Error opening heredoc file");
		free(file_name);
		return (-1);
	}
	loop_here_doc(delimiter, fd_out);
	close(fd_out);
	fd_in = open(file_name, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening heredoc file for reading");
		free(file_name);
		return (-1);
	}
	unlink(file_name);
	free(file_name); // Libère la mémoire allouée au nom de fichier
	return (fd_in);  // Retourne le descripteur de fichier
}
