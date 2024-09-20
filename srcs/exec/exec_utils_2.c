/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:31:04 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/20 16:22:35 by jules            ###   ########.fr       */
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

void	execute_process(t_shell *shell, t_cmd *current_cmd, t_fd *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_all_fds(fds);
		exit_shell(shell, "Error: Fork");
	}
	else if (pid == 0)
	{
		// Exécution du processus enfant
		execute_child(shell, current_cmd, fds);
		if (current_cmd)
		{
			run_builtins(shell, current_cmd, fds);
			execute_child(shell, current_cmd, fds);
		}
	}
	// Fermeture des FDs du parent après fork
	close_fds_parent(fds);
	fds->input = fds->pipes[0];
}
