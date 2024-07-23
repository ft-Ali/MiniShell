/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/23 18:25:36 by alsiavos         ###   ########.fr       */
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
			print_lexer_list(lex);
			free_tokens(lex);
			free(input);
		}
	}
}
