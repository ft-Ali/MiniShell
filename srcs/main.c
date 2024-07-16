/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/16 11:56:54 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*input;
	t_lex		*lexer;
	// t_lex		*tmp;
 	t_shell shell;

	shell.cmd = NULL;
    shell.env = NULL;
    shell.path = NULL;
	while (1)
	{
		input = readline(CYAN "[づ ◕‿◕ )づ] --> " RESET);
		if (input)
		{
			add_history(input);
			lexer = tokenize(&shell ,input);
			expander(lexer);
 			print_tokens(lexer);
			// while (lexer)
			// {
			// 	tmp = lexer;
			// 	lexer = lexer->next;
			// 	free(tmp->word);
			// 	free(tmp);
			// }
			free(input);
		}
	}
}

