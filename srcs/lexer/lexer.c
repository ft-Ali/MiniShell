/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/15 13:56:28 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lexer	*new_token(t_token token, char *str)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	add_token(t_lexer **lexer, t_token token, char *str)
{
	t_lexer	*new;

	new = new_token(token, str);
	if (!new)
	{
		perror("Failed to allocate memory for new token");
		return ;
	}
	new->next = *lexer;
	*lexer = new;
}

void	tokenize(t_lexer **lexer, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (special_check(lexer, input, &i) == 0)
			word(lexer, input, &i);
		i++;
	}
}

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
