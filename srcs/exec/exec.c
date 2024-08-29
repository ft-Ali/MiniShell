/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:03 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/29 14:51:50 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	exec(t_shell *shell, t_cmd *cmd)
// {
// 	pid_t	pid;
// 	int		status;

// 	char	**env;

// 	env = env_list_to_envp(shell->env);
// 	print_envp(env);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd->commands[0], cmd->commands, env) == -1)
// 		{
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid < 0)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		print_envp(env);
// 		waitpid(pid, &status, 0);
// 	}
// }

// void	exec_cmds(t_shell *shell, t_cmd *cmd)
// {
// 	char	**env;

// 	env = env_list_to_envp(shell->env);
// 	print_envp(env);
// 	while (cmd)
// 	{
// 		exec(shell, cmd);
// 		cmd = cmd->next;
// 	}
// }


/*
YA RIEN QUI MARCHE MAIS TQT BIENTOT


*/