/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/15 14:31:28 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_tokens(t_lexer *lexer)
{
	const char	*token_names[] = {"WORD", "STRING", "PIPE", "GREATER", "D_GREATER", "LOWER",
		"D_LOWER"};
	while (lexer)
	{
		ft_printf(RED "Token: [%s] && Value [%s]\n", token_names[lexer->token],
			lexer->str);
		lexer = lexer->next;
	}
}
