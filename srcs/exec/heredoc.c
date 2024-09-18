/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:57:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/18 15:04:51 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:00:00 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/18 15:00:00 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Gestion du heredoc (<<)
static void	create_heredoc_file(char *delimiter)
{
	char	*temp_file;
	int		fd;
	char	*line;

	temp_file = "heredoc.tmp";
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = NULL;
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline(RED "> " RESET);
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

/**
 * Gère la redirection heredoc.
 */
void	handle_heredoc(char *delimiter)
{
	int	fd;

	create_heredoc_file(delimiter);
	fd = open("heredoc.tmp", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}
