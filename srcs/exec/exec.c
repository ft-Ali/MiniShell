/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/16 14:38:09 by alsiavos         ###   ########.fr       */
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
			printf("Found executable at: %s\n", full_path);
			free(path);
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(path);
	free(paths);
	return (NULL);
}

// Exécuter une commande avec gestion des erreurs

void	exec_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**envp;

	envp = env_list_to_envp(shell->env);
	cmd_path = find_cmd_path(shell, cmd->commands[0]); // Pass the correct type
	printf("cmd_path: %s\n", cmd_path);
	if (cmd_path)
	{
		if (execve(cmd_path, cmd->commands, envp) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("%s: command not found\n", cmd->commands[0]);
		// exit(127);
	}
	free(cmd_path);
	free_envp(envp);
}

// Gérer les redirections de sortie
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

// Exécuter la commande avec gestion des redirections et des pipes
// Fonction pour exécuter une commande
void	exec(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	t_redir	*current_redir;
	char	*cmd_path;
	char	**envp;

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
	{
		printf("Child process created.\n");
		// Gérer les redirections avant d'exécuter la commande
		current_redir = cmd->redir;
		while (current_redir)
		{
			if (current_redir->token == LOWER
				|| current_redir->token == D_LOWER)
				handle_redirection_in(current_redir->file);
			else if (current_redir->token == GREATER
				|| current_redir->token == D_GREATER)
				handle_redirection_out(current_redir->file);
			current_redir = current_redir->next;
		}
		// Trouver le chemin de la commande
		cmd_path = find_cmd_path(shell, cmd->commands[0]);
		printf("Command Path: %s\n", cmd_path);
		printf("Command: %s\n", cmd->commands[0]);
		if (cmd_path)
		{
			envp = env_list_to_envp(shell->env);
			if (!envp)
			{
				perror("env_list_to_envp failed");
				exit(EXIT_FAILURE);
			}
			if (execve(cmd_path, cmd->commands, envp) == -1)
			{
				perror("execve failed");
				free_envp(envp);
				exit(EXIT_FAILURE);
			}
			free_envp(envp);
			free(cmd_path);
		}
		else
		{
			printf("%s: command not found\n", cmd->commands[0]);
			exit(127);
		}
	}
	else
	{
		printf("Waiting for child process to finish.\n");
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			shell->last_exit_status = WEXITSTATUS(status);
			printf("Child process exited with status %d\n",
				shell->last_exit_status);
		}
	}
}
