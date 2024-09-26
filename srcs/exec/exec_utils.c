/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:01:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 14:45:42 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	run_builtins(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
	child_builtins(shell, fds);
	if (ft_strncmp(cmd->commands[0], "echo", 4) == 0
		&& ft_strlen(cmd->commands[0]) == 4)
		bi_echo(shell, cmd, fds->output, fds);
	else if (ft_strncmp(cmd->commands[0], "env", 3) == 0
		&& ft_strlen(cmd->commands[0]) == 3)
		bi_env(shell, cmd, fds->output, fds);
	else if (ft_strncmp(cmd->commands[0], "pwd", 3) == 0
		&& ft_strlen(cmd->commands[0]) == 3)
		bi_pwd(shell, cmd, fds->output, fds);
}

void	child_builtins(t_shell *shell, t_fd *fds)
{
	if (fds->input != -2)
		close(fds->input);
	if (fds->output == -2)
		fds->output = dup(STDOUT_FILENO);
	if (fds->output == -1)
		(close_all_fds(fds), exit_shell(shell, "Error : dup2"));
}

char	*get_cmd_path(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
	if (ft_strchr(cmd->commands[0], '/') != NULL)
	{
		if (is_dir(cmd->commands[0]))
		{
			ft_putstr_fd(cmd->commands[0], STDOUT_FILENO);
			ft_putstr_fd(": Is a directory\n", STDOUT_FILENO);
			shell->excode = 126;
			close_all_fds(fds);
			exit_shell(shell, "");
		}
		else if (access(cmd->commands[0], F_OK | X_OK) == 0)
			return (ft_strdup(cmd->commands[0]));
	}
	else
	{
		return (find_cmd_path(shell, cmd->commands[0]));
	}
	return (NULL);
}

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
	exec_cmd(shell, cmd, fds);
}
