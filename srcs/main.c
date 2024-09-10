/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/10 10:55:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_shell(t_shell *shell, char *error_msg)
{
	perror(error_msg);
	free_shell(shell);
	exit(EXIT_FAILURE);
}

int	main(int c, char **v, char **envp)
{
	char	*input;
	t_lex	*lex;
	t_shell	shell;
	char	**env;

	if (c != 1)
		return (1);
	(void)v;
	load_env(&shell, envp);            // Charge envp dans shell.env
	env = env_list_to_envp(shell.env); // Charge shell.env dans env
	print_envp(env);                   // Affiche env
	shell.cmd = NULL;
	shell.env = NULL;
	shell.path = NULL;
	while (1)
	{
		input = readline(CYAN "$ ->" RESET);
		if (input)
		{
			add_history(input);
			lex = lexer(&shell, input);
			expander(lex);
			parser(&shell.cmd, lex);
			// if (shell.cmd)
			// 	exec_cmds(&shell, shell.cmd);
			free_lex(lex);
			free_cmd(shell.cmd);
			free(input);
		}
	}
}
