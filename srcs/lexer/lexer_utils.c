/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:50:48 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/12 15:43:44 by jpointil         ###   ########.fr       */
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
