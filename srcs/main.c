/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/20 16:28:17 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/09/20 16:18:55 by jules            ###   ########.fr       */
>>>>>>> 52586e74b63b60f35a57084c5d004a05e5395ef3
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_sig = 0;

void	reset_loop(t_shell *shell)
{
	if (shell->lex)
		free_lex(shell->lex);
	if (shell->cmd)
		free_cmd(shell->cmd);
	shell->cmd = NULL;
	shell->lex = NULL;
}

void	exit_shell(t_shell *shell, char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	free_shell(shell);
	exit(EXIT_FAILURE);
}

void	init_shell(t_shell *shell)
{
	shell->tmpexcode = 0;
	shell->excode = 0;
	shell->cmd = NULL;
	shell->env = NULL;
	shell->path = NULL;
	shell->lex = NULL;
}

int	main(int c, char **v, char **envp)
{
	char	*input;
	t_lex	*lex;
	t_shell	shell;

	if (c != 1)
		return (printf("Error : no args needed\n"), 0);
	(void)v;
	init_shell(&shell);
	init_sig();
	load_env(&shell, envp); // Charge envp dans shell.env
	// print_env(shell.env);                   // Affiche env
	while (1)
	{
		input = readline(CYAN "$ ->" RESET);
		if (input)
		{
			add_history(input);
			lex = lexer(&shell, input);
			expander(lex);
			parser(&shell, &shell.cmd, lex);
			// print_parser(shell.cmd);
			exec(&shell, shell.cmd);
			// free_lex(lex);
			// free_cmd(shell.cmd);
			// free_cmd(shell.cmd);
			free(input);
			free_loop(&shell);
		}
		else
			exit_shell(&shell, NULL);
	}
}
