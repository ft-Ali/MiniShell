/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:04 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/24 16:49:11 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_fds_and_redirections(t_shell *shell, t_cmd *current_cmd, t_fd *fds)
{
	init_fds(fds);
	if (current_cmd->next)
	{
		if (pipe(fds->pipes) == -1)
			exit_shell(shell, "Error: pipe");
	}
	apply_redirections(current_cmd, &fds->redir[0], &fds->redir[1]);
	set_fds(fds);
}

int	handle_builtins(t_shell *shell, t_cmd *current_cmd)
{
	if (ft_strncmp(current_cmd->commands[0], "exit", 4) == 0
		&& ft_strlen(current_cmd->commands[0]) == 4)
	{
		bi_exit(shell, current_cmd);
		return (1);
	}
	else if (ft_strncmp(current_cmd->commands[0], "cd", 2) == 0
		&& ft_strlen(current_cmd->commands[0]) == 2)
	{
		bi_cd(shell, current_cmd);
		return (1);
	}
	else if (ft_strncmp(current_cmd->commands[0], "export", 6) == 0
		&& ft_strlen(current_cmd->commands[0]) == 6)
	{
		bi_export(shell, current_cmd);
		return (1);
	}
	else if (ft_strncmp(current_cmd->commands[0], "unset", 5) == 0
		&& ft_strlen(current_cmd->commands[0]) == 5)
	{
		bi_unset(shell, current_cmd);
		return (1);
	}
	return (0);
}
int	is_builtin_command(const char *command)
{
	if (ft_strncmp(command, "exit", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	else if (ft_strncmp(command, "cd", 2) == 0 && ft_strlen(command) == 2)
		return (1);
	else if (ft_strncmp(command, "export", 6) == 0 && ft_strlen(command) == 6)
		return (1);
	else if (ft_strncmp(command, "unset", 5) == 0 && ft_strlen(command) == 5)
		return (1);
	else if (ft_strncmp(command, "env", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	else if (ft_strncmp(command, "echo", 4) == 0 && ft_strlen(command) == 4)
		return (1);
	else if (ft_strncmp(command, "pwd", 3) == 0 && ft_strlen(command) == 3)
		return (1);
	return (0);
}

int	is_dir(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

void	execute_process(t_shell *shell, t_cmd *current_cmd, t_fd *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_all_fds(fds);
		exit_shell(shell, "Error: Fork");
	}
	else if (pid == 0) // Processus enfant
	{
		if (is_builtin_command(current_cmd->commands[0]))
		{
			// Si c'est un builtin,on exécute le builtin dans le processus enfant
			run_builtins(shell, current_cmd, fds);
			close_all_fds(fds);
			exit(0); // On s'assure de terminer le processus après le builtin
		}
		else
		{
			// Sinon, on exécute une commande externe
			execute_child(shell, current_cmd, fds);
		}
	}
	// Le parent continue ici après fork()
}
