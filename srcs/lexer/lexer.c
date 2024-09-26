/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 10:29:46 by jpointil         ###   ########.fr       */
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
			(*index)++;
			(*count)++;
			*quote_state = 0;
			break ;
		}
		if (*quote_state != 0)
		{
			(*count)++;
			(*index)++;
		}
	}
}

static void	process_word(char *string, int *index, int *length)
{
	while ((string[*index] != ' ') && (is_token(string, *index) == FALSE)
		&& string[*index])
	{
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
			add_new_word(shell, lex, string, (int [2]){index, length});
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
		shell->excode = 2;
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
		return (lex);
	}
	get_shell_sig(shell);
	process_input(shell, &lex, string);
	return (lex);
}
