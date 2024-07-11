/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:50:48 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/11 20:53:38 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_or_not(char c, t_comp comp)
{
	if (comp == REDIR)
		return (c == '<' || c == '>');
	else if (comp == PIPE)
		return (c == '|');
	return (0);
}

int	special_check(t_lexer **lexer, char *input, int *i)
{
	if (is_or_not(input[*i], REDIR))
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
