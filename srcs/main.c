/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:29:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/12 13:36:27 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*token;
	t_token	*tmp;

	while (1)
	{
		input = readline(CYAN "[UN TRUC QUI S'APPEL MINISHELL (づ ◕‿◕ )づ] --> " RESET);
		if (input)
		{
			add_history(input);
			token = NULL;
			tokenize(&token, input);
			// print_tokens(token);
			while (token)
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
