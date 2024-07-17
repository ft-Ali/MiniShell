/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/17 11:48:00 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*input;
	t_lex		*lex;
	// t_lex		*tmp;
 	t_shell shell;

	shell.cmd = NULL;
    shell.env = NULL;
    shell.path = NULL;
	while (1)
	{
		input = readline("$->");
		if (input)
		{
			add_history(input);
			lex = lexer(&shell ,input);
 			// print_list(&shell);
			expander(lex); 
			// print_tokens(lexer);
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

