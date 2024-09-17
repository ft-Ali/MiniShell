/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/17 17:09:14 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Libérer la mémoire utilisée pour l'environnement
void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

// Fonction pour trouver le chemin de la commande
char	*find_cmd_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;

	path = get_value_by_key("PATH", shell->env);
	if (!path)
	{
		printf("PATH variable not found in env.\n");
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path); // Libération de la mémoire de path ici
	if (!paths)
	{
		perror("ft_split failed");
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = strjoin_free(full_path, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(paths); // Libération de la mémoire des paths
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths); // Libération de la mémoire des paths
	return (NULL);
}

// Exécuter une commande avec gestion des erreurs
void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**envp;

	if (!cmd || !cmd->commands[0])
		return ;
	envp = env_list_to_envp(shell->env);
	cmd_path = find_cmd_path(shell, cmd->commands[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", cmd->commands[0]);
		free_envp(envp);
		exit(127); // Exit with command not found status
	}
	if (execve(cmd_path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
		free(cmd_path);
		free_envp(envp);
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
	free_envp(envp);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**envp;

	if (!cmd || !cmd->commands[0])
		return ;
	cmd_path = find_cmd_path(shell, cmd->commands[0]);
	if (!cmd_path)
	{
		printf("%s: command not found\n", cmd->commands[0]);
		return ;
	}
	envp = env_list_to_envp(shell->env);
	if (execve(cmd_path, cmd->commands, envp) == -1)
	{
		perror("execve failed");
	}
	free(cmd_path);
	free_envp(envp);
}

void	handle_redirection_out(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open failed for output redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO); // Rediriger la sortie vers ce fichier
	close(fd);
}

void	handle_redirection_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed for input redirection");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO); // Rediriger l'entrée depuis ce fichier
	close(fd);
}
