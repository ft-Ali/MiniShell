/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/19 17:50:22 by alsiavos         ###   ########.fr       */
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
	free(path);
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
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free(paths);
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
		exit(127);
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

void	execute_child(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
	if (fds->pipes[0] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		if (dup2(fds->input, STDIN_FILENO) == -1)
			(close_all_fds(fds), exit_shell(shell, ""));
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit_shell(shell, ""));
	close_all_fds(fds);
	exec_cmd(shell, cmd);
}
// void	execute_cmd(t_shell *shell, t_cmd *cmd, t_fd *fds)
// {
// 	// if (cmd->builtin == EXIT)
// 	// 	ft_exit(shell, cmd, fds);
// 	// else if (cmd->builtin == CD)
// 	// 	ft_cd(shell, cmd);
// 	// else if (cmd->builtin == EXPORT)
// 	// 	ft_export(&shell->env, cmd, shell);
// 	// else if (cmd->builtin == UNSET)
// 	// 	ft_unset_builtin(shell, cmd);
// 	// else
// 	// {
// }
// Exécuter une liste de commandes en boucle avec gestion des redirections et des erreurs
void	wait_child(t_shell *shell)
{
	int		status;
	pid_t	pid;

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

// void	is_builtin(t_cmd *cmd)
// {
// 	if (cmd && cmd->commands != NULL)
// 	{
// 		if (ft_strncmp(cmd->commands[0], "echo", 4) == 0
// 			&& ft_strlen(cmd->commands[0]) == 4)
// 			cmd->builtin = ECHO;
// 		else if (ft_strncmp(cmd->commands[0], "cd", 3) == 0
// 			&& ft_strlen(cmd->commands[0]) == 2)
// 			cmd->builtin = CD;
// 		else if (ft_strncmp(cmd->commands[0], "pwd", 3) == 0
// 			&& ft_strlen(cmd->commands[0]) == 3)
// 			cmd->builtin = PWD;
// 		else if (ft_strncmp(cmd->commands[0], "exit", 4) == 0
// 			&& ft_strlen(cmd->commands[0]) == 4)
// 			cmd->builtin = EXIT;
// 		else if (ft_strncmp(cmd->commands[0], "export", 6) == 0
// 			&& ft_strlen(cmd->commands[0]) == 6)
// 			cmd->builtin = EXPORT;
// 		else if (ft_strncmp(cmd->commands[0], "unset", 5) == 0
// 			&& ft_strlen(cmd->commands[0]) == 5)
// 			cmd->builtin = UNSET;
// 		else if (ft_strncmp(cmd->commands[0], "env", 3) == 0
// 			&& ft_strlen(cmd->commands[0]) == 3)
// 			cmd->builtin = ENV;
// 	}
// }

void	child_builtins(t_shell *shell, t_fd *fds)
{
	if (fds->input != -2)
		close(fds->input);
	if (fds->output == -2)
		fds->output = dup(STDOUT_FILENO);
	if (fds->output == -1)
		(close_all_fds(fds), exit_shell(shell, "Error : dup2"));
}

void	run_builtins(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
	child_builtins(shell, fds);
	if (ft_strncmp(cmd->commands[0], "echo", 4) == 0
		&& ft_strlen(cmd->commands[0]) == 4)
		bi_echo(shell, cmd);
	if (ft_strncmp(cmd->commands[0], "env", 3) == 0
		&& ft_strlen(cmd->commands[0]) == 3)
		bi_env(shell, cmd);
	if (ft_strncmp(cmd->commands[0], "pwd", 3) == 0
		&& ft_strlen(cmd->commands[0]) == 3)
		bi_pwd(shell, cmd);
}

void	exec(t_shell *shell, t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	t_fd	fds;
	pid_t	pid;

	// int		status;
	fds.input = -2;
	current_cmd = cmd_list;
	current_cmd->prev = NULL;
	while (current_cmd) // Parcourt chaque commande de la liste
	{
		init_fds(&fds); // Initialisation des FDs
		if (current_cmd->next)
			if (pipe(fds.pipes) == -1)
				exit_shell(shell, "Error : pipe");
		apply_redirections(current_cmd, &fds.redir[0], &fds.redir[1]);
		set_fds(&fds);
		if (current_cmd->commands && current_cmd->commands[0])
		{
			if (ft_strncmp(current_cmd->commands[0], "exit", 4) == 0
				&& ft_strlen(current_cmd->commands[0]) == 4)
				bi_exit(shell, current_cmd, &fds);
			else if (ft_strncmp(current_cmd->commands[0], "cd", 2) == 0
				&& ft_strlen(current_cmd->commands[0]) == 2)
				bi_cd(shell, current_cmd);
			// else if (ft_strncmp(current_cmd->commands[0], "export", 6) == 0
			// && ft_strlen(current_cmd->commands[0]) == 6)
			// 	bi_export(&shell->env, current_cmd, shell);
			else if (ft_strncmp(current_cmd->commands[0], "unset", 5) == 0
				&& ft_strlen(current_cmd->commands[0]) == 5)
				bi_unset(shell, current_cmd);
			pid = fork();
			if (pid == -1)
				(close_all_fds(&fds), exit_shell(shell, "Error : Fork"));
			else if (pid == 0)
			{
				if (current_cmd)
					(run_builtins(shell, current_cmd, &fds)),
						execute_child(shell, current_cmd, &fds);
			}
			close_fds_parent(&fds);
			fds.input = fds.pipes[0];
		}
		if (!current_cmd->next)
			close_fds_parent(&fds);
		if (current_cmd->next)
			current_cmd->next->prev = current_cmd;
		current_cmd = current_cmd->next;
	}
	wait_child(shell);
	close_all_fds(&fds);
}

// 	// Appliquer les redirections et les pipes
// 	apply_redirections(current_cmd, &fds.redir[0], &fds.redir[1]);
// 	set_fds(&fds);
// 	// Exécuter la commande
// 	exec_cmd(shell, current_cmd);
// 	// Fermeture des FDs inutilisés dans le processus enfant
// 	close_all_fds(&fds);
// }
// else // Processus parent
// {
// 	// Fermeture des FDs inutilisés par le parent
// 	close_fds_parent(&fds);
// 	// Attente de la fin du processus enfant
// 	if (waitpid(pid, &status, 0) == -1)
// 	{
// 		perror("waitpid failed");
// 		exit(EXIT_FAILURE); // Sortir si waitpid échoue
// 	}
// 	// Gestion du code de retour du processus enfant
// 	if (WIFEXITED(status))
// 		shell->last_exit_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		shell->last_exit_status = WTERMSIG(status) + 128; // Si signal