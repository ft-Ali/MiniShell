/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/11 18:10:11 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*new_token(t_token token, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **lexer, t_token token, char *str)
{
	t_token	*new;

	new = new_token(token, str);
	if (!new)
	{
		perror("Failed to allocate memory for new token");
		return ;
	}
	new->next = *lexer;
	*lexer = new;
}

void	tokenize(t_token **lexer, char *input)
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

/* void	print_tokens(t_token *lexer)
{
	const char	**token_names;

	token_names = "WORD", "STRING", "PIPE", "GREATER", "D_GREATER", "LOWER",
		"D_LOWER";
	while (lexer)
	{
		ft_printf(RED "Token: [%s] && Value [%s]\n", token_names[lexer->token],
			lexer->str);
		lexer = lexer->next;
	}
} */
