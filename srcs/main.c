/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/08 11:24:02 by alsiavos         ###   ########.fr       */
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
	shell->tmpexcode = shell->excode;
	shell->excode = 0;
}

void	exit_shell(t_shell *shell, char *error_msg)
{
	int	tmp;

	if (shell->excode != 0)
		tmp = shell->excode;
	else
		tmp = shell->tmpexcode;
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	free_shell(shell);
	exit(tmp);
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
	char	*expanded;

	if (c != 1)
		return (printf("Error : no args needed\n"), 0);
	((void)v, init_shell(&shell), init_sig(), load_env(&shell, envp));
	while (1)
	{
		get_shell_sig(&shell); // rajoute post correction
		input = readline(CYAN "$ ->" RESET);
		if (input)
		{
			add_history(input);
			expanded = expander(input, &shell);
			lex = lexer(&shell, expanded);
			(free(expanded), parser(&shell, &shell.cmd, lex));
			if (shell.cmd)
				exec(&shell, shell.cmd);
			free(input);
			free_loop(&shell);
		}
		else
			exit_shell(&shell, NULL);
	}
}
