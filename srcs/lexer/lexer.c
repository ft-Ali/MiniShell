/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/18 11:48:41 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_quote(char *string, int *index, int *count, int *quote_state)
{
	*quote_state = is_quote(string[(*index)++]);
	(*count)++;
	while (*quote_state != 0 && string[*index])
	{
		if (is_quote(string[*index]) == *quote_state)
		{
			while ((*quote_state == is_quote(string[(*index)]))
				&& string[(*index)])
			{
				(*index)++;
				(*count)++;
			}
			*quote_state = 0;
			break ;
		}
		(*count)++;
		(*index)++;
	}
}

static void	process_word(char *string, int *index, int *length)
{
	int	quote_state;

	quote_state = 0;
	while ((string[*index] != ' ') && (is_token(string, *index) == FALSE)
		&& string[*index])
	{
		quote_state = is_quote(string[*index]);
		if (quote_state != 0)
		{
			(*index)++;
			(*length)++;
			while (string[*index] && quote_state != is_quote(string[*index]))
			{
				(*index)++;
				(*length)++;
			}
		}
		(*length)++;
		(*index)++;
	}
}

static void	process_input(t_shell *shell, t_lex **lex, char *string)
{
	int	index;
	int	length;
	int	quote_state;

	index = 0;
	quote_state = 0;
	while (string[index])
	{
		while (string[index] && (string[index] == ' ' || (string[index] >= 7
					&& string[index] <= 13)))
			index++;
		length = 0;
		if ((string[index] == '\'') || (string[index] == '\"'))
			process_quote(string, &index, &length, &quote_state);
		else
			process_word(string, &index, &length);
		if (length > 0)
			add_new_word(shell, lex, string, (int[2]){index, length});
		if (is_token(string, index) != FALSE)
			(add_new_token(shell, lex, is_token(string, index)), index++);
		if (is_token(string, index - 1) == D_GREATER || is_token(string, index
				- 1) == D_LOWER)
			index++;
	}
}
t_lex	*lexer(t_shell *shell, char *string)
{
	t_lex	*lex;

	lex = NULL;
	if (check_opened_quote(string) == FALSE)
	{
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
		return (lex);
	}
	process_input(shell, &lex, string);
	return (lex);
}

// void	print_tokens(t_lex *lexer)
// {
// 	t_token 
// 	while (lexer)
// 	{
// 		if (lexer->word)
// 			ft_printf("Token: [%s] Value [%s]\n", ,lexer->word);
// 		lexer = lexer->next;
// 	}
// }
