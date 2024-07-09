/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:29:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/09 13:29:04 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*input;
	t_lexer	*lexer;
	t_lexer	*tmp;

	while (1)
	{
		input = readline(BOLD_PURPLE "[SumimaShell (づ ◕‿◕ )づ] --> " RESET);
		if (input)
		{
			add_history(input);
			lexer = NULL;
			tokenize(&lexer, input);
			print_tokens(lexer);
			while (lexer)
			{
				tmp = lexer;
				lexer = lexer->next;
				free(tmp->str);
				free(tmp);
			}
			free(input);
		}
	}
}
