/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/26 00:05:33 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lexer_list(t_lex *head)
{
	t_lex *current = head;
	while (current != NULL)
	{
		printf("Token: %d\n", current->token);
		printf("Word: %s\n", current->word);
		printf("\n");
		current = current->next;
	}
}
int	main(void)
{
	char	*input;
	t_lex	*lex;
	t_shell	shell;

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
			parser(&shell, lex);
			// print_parser_result(shell.cmd);
			// print_lexer_list(lex);
			free_tokens(lex);
			free(input);
		}
	}
}
