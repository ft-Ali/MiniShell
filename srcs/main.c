/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/21 16:15:27 by alsiavos         ###   ########.fr       */
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

	(void)c;
	(void)v;
	shell.cmd = NULL;
	shell.env = NULL;
	shell.path = NULL;
	load_environment(&shell, envp);
	// print_env_list(shell.env);
	while (1)
	{
		input = readline(CYAN "$ ->" RESET);
		if (input)
		{
			add_history(input);
			lex = lexer(&shell, input);
			expander(lex);
			parser(&shell.cmd, lex);
			print_parser(shell.cmd);
			free_tokens(lex);
			free_cmd(shell.cmd);
			free(input);
		}
	}
}
