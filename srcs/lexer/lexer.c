/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:38:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/30 18:01:30 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// void	process_quote(char *string, int *index, int *count, int *d_quote)
// {
// 	*d_quote = is_quote(string[(*index)++]);
// 	(*count)++;
// 	while (*d_quote != 0 && string[*index])
// 	{
// 		if (is_quote(string[*index]) == *d_quote)
// 		{
// 			(*index)++;
// 			(*count)++;
// 			*d_quote = 0;
// 			break ;
// 		}
// 		if (*d_quote != 0)
// 		{
// 			(*count)++;
// 			(*index)++;
// 		}
// 	}
// }

static void	process_word(char *string, int *index, int *length, int flag)
{
	int	s_quote;
	int	d_quote;

	s_quote = -2;
	d_quote = -1;
	while (string[*index])
	{
		flag = is_quote(string[*index]);
		if (flag)
		{
			if (flag == 1)
				d_quote *= -1;
			else if (flag == 2)
				s_quote *= -1;
		}
		else if ((string[*index] == ' ' || is_token(string, *index) != FALSE)
			&& d_quote == -1 && s_quote == -2)
		{
			break ;
		}
		(*length)++;
		(*index)++;
	}
}

static void	process_input(t_shell *shell, t_lex **lex, char *string)
{
	int	index;
	int	length;

	index = 0;
	while (string[index])
	{
		while (string[index] && (string[index] == ' ' || (string[index] >= 7
					&& string[index] <= 13)))
			index++;
		length = 0;
		process_word(string, &index, &length, 0);
		if (length > 0)
			add_new_word(shell, lex, string, (int [2]){index, length});
		if (is_token(string, index) != FALSE)
		{
			add_new_token(shell, lex, is_token(string, index));
			index++;
		}
		if ((is_token(string, index - 1) == D_GREATER || is_token(string, index
					- 1) == D_LOWER))
			index++;
	}
}

t_lex	*lexer(t_shell *shell, char *string)
{
	t_lex	*lex;

	lex = NULL;
	if (!string)
		return (NULL);
	if (check_opened_quote(string) == FALSE)
	{
		shell->excode = 2;
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
		return (lex);
	}
	get_shell_sig(shell);
	process_input(shell, &lex, string);
	lex = trimquote_process(lex);
	return (lex);
}
