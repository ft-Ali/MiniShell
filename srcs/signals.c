/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:57:31 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/26 15:16:01 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sig(int sig)
{
	g_sig = sig;
	if (wait(NULL) != -1)
	{
		if (sig == SIGQUIT)
			printf("Quit (core dumped)");
		printf("\n");
	}
	else if (sig == SIGINT)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		g_sig = 0;
}

void	handle_sig_heredoc(int sig)
{
	g_sig = sig;
	write(STDOUT_FILENO, "^C", 3);
}

void	init_sig_heredoc(void)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sig.sa_handler = &handle_sig_heredoc;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGINT, &sig, NULL);
}

void	init_sig(void)
{
	struct sigaction	sig;

	rl_catch_signals = 0;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sig.sa_handler = &handle_sig;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGTERM, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

bool	get_shell_sig(t_shell *shell)
{
	if (g_sig == SIGINT)
	{
		shell->excode = 130;
		g_sig = 0;
		return (true);
	}
	else if (g_sig == SIGQUIT)
	{
		shell->excode = 131;
		g_sig = 0;
		return (true);
	}
	return (false);
}
