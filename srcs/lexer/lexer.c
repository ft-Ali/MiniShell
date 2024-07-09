/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/09 14:27:41 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

t_lexer	*new_token(t_token token, char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->i = 0;
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	add_token(t_lexer **lexer, t_token token, char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	new->token = token;
	new->str = str;
	new->next = *lexer;
	*lexer = new;
}

void	tokenize(t_lexer **lexer, char *input)
{
	int i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		special_check(lexer, input, &i);
		word_string(lexer, input, &i);
		i++;
	}
}

void	print_tokens(t_lexer *lexer)
{
	const char	*token_names[] = {"WORD", "STRING", "PIPE", "GREATER",
			"D_GREATER", "LOWER", "D_LOWER"};

	while (lexer)
	{
		ft_printf(RED "Token: [%s] && Value [%s]\n", token_names[lexer->token],
			lexer->str);
		lexer = lexer->next;
	}
}
