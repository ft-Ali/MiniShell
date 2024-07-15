/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:29:41 by alsiavos          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/15 11:29:30 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/07/12 15:59:54 by alsiavos         ###   ########.fr       */
>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*input;
	
	while (1)
	{
		input = readline(CYAN "[UN TRUC QUI S'APPEL MINISHELL (づ ◕‿◕ )づ] --> " RESET);
		if (input)
		{
			add_history(input);
<<<<<<< HEAD
			lexer = NULL;
			tokenize(&lexer, input);
			expander(lexer);
			print_tokens(lexer);
			while (lexer)
=======
<<<<<<< HEAD
			token = NULL;
			tokenize(&token, input);
			// print_tokens(token);
			while (token)
>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
			{
				tmp = token;
				token = token->next;
				free(tmp->str);
				free(tmp);
			}
			free(input);
		}
	}
}
