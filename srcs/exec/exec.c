/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/28 15:16:43 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exec(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	char **env;

	pid = fork();
	if (pid < 0)
		exit_shell(shell, "Error: fork failed");
	if (pid == 0)
	{
		if (execve(cmd->commands[0], cmd->commands, load_env(env)) < 0)
			exit_shell(shell, "Error: execve failed");
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

void	exec_cmds(t_shell *shell, t_cmd *cmd)
{
	while (cmd)
	{
		exec(shell, cmd);
		cmd = cmd->next;
	}
}

