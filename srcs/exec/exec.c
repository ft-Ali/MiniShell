/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/20 15:46:27 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_paths_from_env(t_shell *shell)
{
	char	*path;
	char	**paths;

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
	return (paths);
}

// Fonction pour trouver le chemin de la commande
char	*find_cmd_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = get_paths_from_env(shell);
	if (!paths)
		return (NULL);
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

void	exec(t_shell *shell, t_cmd *cmd_list)
{
	t_cmd	*current_cmd;
	t_fd	fds;

	fds.input = -2;
	current_cmd = cmd_list;
	current_cmd->prev = NULL;
	while (current_cmd)
	{
		init_fds_and_redirections(shell, current_cmd, &fds);
		if (current_cmd->commands && current_cmd->commands[0])
		{
			// Si la commande est une commande intégrée (built-in), on la gère et on continue
			handle_builtins(shell, current_cmd);
			execute_process(shell, current_cmd, &fds);
		}
		if (!current_cmd->next)
			close_fds_parent(&fds);
		if (current_cmd->next)
			current_cmd->next->prev = current_cmd;
		current_cmd = current_cmd->next;
	}
	wait_child(shell);   // Attente de la fin des processus enfants
	close_all_fds(&fds); // Fermeture des FDs après l'exécution
}

// void	exec(t_shell *shell, t_cmd *cmd_list)
// {
// 	t_cmd	*current_cmd;
// 	t_fd	fds;
// 	pid_t	pid;

// 	fds.input = -2;
// 	current_cmd = cmd_list;
// 	current_cmd->prev = NULL;
// 	while (current_cmd)
// 	{
// 		init_fds(&fds);
// 		if (current_cmd->next)
// 			if (pipe(fds.pipes) == -1)
// 				exit_shell(shell, "Error : pipe");
// 		apply_redirections(current_cmd, &fds.redir[0], &fds.redir[1]);
// 		set_fds(&fds);
// 		if (current_cmd->commands && current_cmd->commands[0])
// 		{
// 			if (ft_strncmp(current_cmd->commands[0], "exit", 4) == 0
// 				&& ft_strlen(current_cmd->commands[0]) == 4)
// 				bi_exit(shell, current_cmd);
// 			else if (ft_strncmp(current_cmd->commands[0], "cd", 2) == 0
// 				&& ft_strlen(current_cmd->commands[0]) == 2)
// 				bi_cd(shell, current_cmd);
// 			// else if (ft_strncmp(current_cmd->commands[0], "export",
// 			// 6) == 0
// 			// && ft_strlen(current_cmd->commands[0]) == 6)
// 			// 	bi_export(&shell->env, current_cmd, shell);
// 			else if (ft_strncmp(current_cmd->commands[0], "unset", 5) == 0
// 				&& ft_strlen(current_cmd->commands[0]) == 5)
// 				bi_unset(shell, current_cmd);
// 			pid = fork();
// 			if (pid == -1)
// 				(close_all_fds(&fds), exit_shell(shell, "Error : Fork"));
// 			else if (pid == 0)
// 			{
// 				execute_child(shell, current_cmd, &fds); //
// 				if (current_cmd)
// 					(run_builtins(shell, current_cmd, &fds)),
// 						execute_child(shell, current_cmd, &fds);
// 			}
// 			close_fds_parent(&fds);
// 			fds.input = fds.pipes[0];
// 		}
// 		if (!current_cmd->next)
// 			close_fds_parent(&fds);
// 		if (current_cmd->next)
// 			current_cmd->next->prev = current_cmd;
// 		current_cmd = current_cmd->next;
// 	}
// 	wait_child(shell);
// 	close_all_fds(&fds);
// }

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
