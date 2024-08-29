/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/29 14:51:59 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer_list(t_lex *head)
{
	t_lex	*current;

	current = head;
	while (current != NULL)
	{
		printf("Token: %d\n", current->token);
		printf("Word: %s\n", current->word);
		printf("\n");
		current = current->next;
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		printf(" %s: %s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*redir;
	int		i;

	while (cmd)
	{
		if (cmd->commands)
		{
			i = -1;
			while (cmd->commands[++i])
				free(cmd->commands[i]);
			free(cmd->commands);
		}
		while (cmd->redir)
		{
			redir = cmd->redir;
			free(redir->file);
			cmd->redir = cmd->redir->next;
			free(redir);
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
int	main(int c, char **v, char **envp)
{
	char	*input;
	t_lex	*lex;
	t_shell	shell;

	char **env;
	load_env(&shell, envp);            // Charge envp dans shell.env
	env = env_list_to_envp(shell.env); // Charge shell.env dans env
	print_envp(env);                   // Affiche env
	(void)c;
	(void)v;
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
			free_tokens(lex);
			free_cmd(shell.cmd);
			free(input);
		}
	}
}
