/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:02:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/15 14:06:17 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_or_not(char c, t_token comp)
{
	if (comp == REDIR)
		return (c == '<' || c == '>');
	else if (comp == PIPE)
		return (c == '|');
	return (0);
}
int	isredirection(char c)
{
	return (c == '>' || c == '<');
}

int	ispipe(char c)
{
	return (c == '|');
}

int	special_check(t_lexer **lexer, char *input, int *i)
{
	if (isredirection(input[*i]))
	{
		if (input[*i] == '>' && input[*i + 1] == '>')
		{
			add_token(lexer, D_GREATER, ft_strdup(">>"));
			(*i)++;
		}
		else if (input[*i] == '>')
			add_token(lexer, GREATER, ft_strdup(">"));
		else if (input[*i] == '<' && input[*i + 1] == '<')
		{
			add_token(lexer, D_LOWER, ft_strdup("<<"));
			(*i)++;
		}
		else if (input[*i] == '<')
			add_token(lexer, LOWER, ft_strdup("<"));
		return (1);
	}
	else if (input[*i] == '|')
	{
		add_token(lexer, PIPE, ft_strdup("|"));
		return (1);
	}
	return (0);
}

void	word(t_lexer **lexer, char *input, int *i)
{
	int		start;
	char	*str;

	start = (*i);
	while (input[*i] && !ft_isspace(input[*i]) && !isredirection(input[*i])
		&& !ispipe(input[*i]))
		(*i)++;
	ft_printf("start 1 = %d \n", start);
	str = ft_strndup(&input[start], *i - start);
	ft_printf("start 2 = %d \n", start);
	add_token(lexer, WORD, str);
	ft_printf("start 3 = %d \n", start);
	(*i)--;
	ft_printf("start 4 = %d \n", start);
}
