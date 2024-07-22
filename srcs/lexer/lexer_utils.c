/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:02:17 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/22 14:38:44 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quote(char quote)
{
	if (quote == '\'')
		return (1);
	if (quote == '\"')
		return (2);
	else
		return (0);
}

int	is_token(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (i++, D_GREATER);
		else
			return (GREATER);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (i++, D_LOWER);
		else
			return (LOWER);
	}
	return (FALSE);
}

static void	check_closed_quote(char *string, char delimiter, int *index,
		int *enclosed)
{
	int	begin;

	begin = *index;
	if (string[*index] == delimiter)
	{
		if (*enclosed == 0)
			*enclosed = -1;
		while (string[*index] && string[*index + 1]
			&& string[++(*index)] != delimiter)
			continue ;
		if (string[*index] == delimiter && *enclosed == -1 && begin != *index)
			*enclosed = 0;
	}
}

int	check_opened_quote(char *string)
{
	int	index;
	int	single_quote_open;
	int	double_quote_open;

	index = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	while (string && string[index])
	{
		if (string[index] == '\'')
			check_closed_quote(string, '\'', &index, &single_quote_open);
		else if (string[index] == '\"')
			check_closed_quote(string, '\"', &index, &double_quote_open);
		index++;
	}
	if (single_quote_open || double_quote_open)
		return (FALSE);
	return (TRUE);
}
