/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:55:05 by jules             #+#    #+#             */
/*   Updated: 2024/09/10 12:18:52 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_lex *lexer)
{
	while (lexer)
	{
		if (lexer->word)
			ft_printf("Token: [%s] Value [%d]\n", lexer->word);
		lexer = lexer->next;
	}
}

void	print_parser(t_cmd *cmd)
{
	int		i;
	t_redir	*current_redir;

	if (!cmd)
	{
		printf("PKO\n");
		return ;
	}
	while (cmd)
	{
		if (cmd->commands)
		{
			printf("cmd: ");
			i = -1;
			while (cmd->commands[++i])
				printf("%s ", cmd->commands[i]);
			printf("\n");
		}
		if (cmd->redir)
		{
			printf("Redirections:\n");
			current_redir = cmd->redir;
			while (current_redir)
			{
				printf("token: %d, file: %s\n", current_redir->token,
					current_redir->file);
				current_redir = current_redir->next;
			}
		}
		cmd = cmd->next;
	}
}

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
