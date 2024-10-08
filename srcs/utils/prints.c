/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:55:05 by jules             #+#    #+#             */
/*   Updated: 2024/10/03 18:47:16 by alsiavos         ###   ########.fr       */
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

// void	print_parser(t_cmd *cmd)
// {
// 	int		i;
// 	t_redir	*current_redir;

// 	if (!cmd)
// 	{
// 		printf("Empty cmd\n");
// 		return ;
// 	}
// 	while (cmd)
// 	{
// 		if (cmd->commands)
// 		{
// 			(printf("cmd: "), i = 0);
// 			while (cmd->commands[i])
// 				(printf("%s ", cmd->commands[i]), i++);
// 			printf("\n");
// 		}
// 		if (cmd->redir)
// 		{
// 			(printf("Redirections:\n"), current_redir = cmd->redir);
// 			while (current_redir)
// 			{
// 				printf("token: %d, file: %s\n", current_redir->token,
// 					current_redir->file);
// 				current_redir = current_redir->next;
// 			}
// 		}
// 		cmd = cmd->next;
// 	}
// }

void	print_lexer_list(t_lex *head)
{
	t_lex	*current;

	current = head;
	while (current != NULL)
	{
		printf(RED "Token: %d\n" RESET, current->token);
		printf(RED "Word: %s\n" RESET, current->word);
		printf("\n");
		current = current->next;
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	printf("Printing env list\n");
	if (!current)
	{
		printf("Empty list\n");
		return ;
	}
	while (current)
	{
		printf(" %s: %s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_env(t_env *env)
{
	printf(RED "Printing env\n" RESET);
	if (!env)
	{
		printf("Empty env\n");
		return ;
	}
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	print_env2(t_env *env)
{
	printf("Printing env\n");
	if (!env)
	{
		printf("Empty env\n");
		return ;
	}
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
