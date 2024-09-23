/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/23 23:28:49 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_sig = 0;

void	init_shell_input(t_shell *shell, char *input)
{
	if (!input)
		return ;
	shell->input = ft_strdup(input);
	if (!shell->input)
		exit_shell(shell, A_ERR);
}

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
	shell->input = NULL;
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
	load_env(&shell, envp);
	while (1)
	{
		input = readline(CYAN "$ ->" RESET);
		if (input)
		{
			add_history(input);
			lex = lexer(&shell, input);
			expander(lex, shell.env);
			parser(&shell, &shell.cmd, lex);
			// init_shell_input(&shell, input);
			exec(&shell, shell.cmd);
			free(input);
			free_loop(&shell);
		}
		else
			exit_shell(&shell, NULL);
	}
}
