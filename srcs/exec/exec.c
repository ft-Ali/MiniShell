/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 14:48:01 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_paths_from_env(t_shell *shell)
{
	char	*path;
	char	**paths;

	path = get_value_by_key("PATH", shell->env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
	{
		perror("ft_split failed");
		return (NULL);
	}
	return (paths);
}

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
		free(paths[i]);
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

void	exec_cmd(t_shell *shell, t_cmd *cmd, t_fd *fds)
{
	char	**envp;

	if (!cmd || !cmd->commands[0])
		return ;
	envp = env_list_to_envp(shell->env, 0, 0);
	if (!cmd || !cmd->commands || cmd->commands[0][0] == '\0')
		exit_shell(shell, "");
	cmd->cmd_path = get_cmd_path(shell, cmd, fds);
	if (!cmd->cmd_path)
	{
		free_envp(envp);
		printf("%s: command not found\n", cmd->commands[0]);
		exit_shell(shell, "");
	}
	if (execve(cmd->cmd_path, cmd->commands, envp) == -1)
	{
		ft_free_split(envp);
		exit_shell(shell, "Error : execve");
	}
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
			if (!(handle_builtins(shell, current_cmd)))
				execute_process(shell, current_cmd, &fds);
		}
		close_fds_parent(&fds);
		fds.input = fds.pipes[0];
		if (!current_cmd->next)
			close_fds_parent(&fds);
		if (current_cmd->next)
			current_cmd->next->prev = current_cmd;
		current_cmd = current_cmd->next;
	}
	wait_child(shell);
	close_all_fds(&fds);
}
