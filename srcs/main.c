/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:28 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/19 11:16:32 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char		*input;
	t_lex		*lex;
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
			expander(lex);
			// while (lex)
			// {
			// 	printf("word : %s, token : %d\n", lex->word, lex->token);
			// 	lex = lex->next;
			// }
			//parser(&shell, lex);
			free_tokens(lex);
			free(input);
		}
	}
}
