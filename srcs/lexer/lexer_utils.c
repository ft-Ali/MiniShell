/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:50:48 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/09 15:06:56 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

int	isRedirection(char c)
{
	return (c == '>' || c == '<');
}

int	isPipe(char c)
{
	return (c == '|');
}


void	special_check(t_lexer **lexer, char *input, int *i)
{
	if (isRedirection(*i))
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
			add_token(lexer, D_GREATER, ft_strdup("<<"));
			(*i)++;
		}
		else if (input[*i] == '<')
			add_token(lexer, LOWER, ft_strdup('<'));
	}
	else if (input[*i] == '|')
		add_token(lexer, PIPE, ft_strdup('|'));
}
void word_string(t_lexer **lexer, char *input, int *i)
{
	int start;
	char *str;

	if(input[*i] == '"')
	{
		start = ++(*i);
		while(input[*i] != '"')
			zebi je suis perdu
	}
}