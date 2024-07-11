/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/11 20:57:57 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_type type, char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->token = token;
    new->prev =  NULL;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **lexer, t_type token, char *str)
{
	t_token	*new;

	new = new_token(token, str);
	if (!new)
	{
		perror("Failed to allocate memory for new token");
		return ;
	}
	new->next = *lexer;
    *lexer->prev = new;
	*lexer = new;
}

void	word(t_lexer **lexer, char *input, int *i)
{
	int		start;
	char	*str;

	start = (*i);
	while (input[*i] && !ft_isspace(input[*i]) && !is_or_not(input[*i], REDIR)
		&& !is_or_not(input[*i], PIPE))
		(*i)++;
	ft_printf("start 1 = %d \n", start);
	str = ft_strndup(&input[start], *i - start);
	ft_printf("start 2 = %d \n", start);
	add_token(lexer, WORD, str);
	ft_printf("start 3 = %d \n", start);
	(*i)--;
	ft_printf("start 4 = %d \n", start);
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
