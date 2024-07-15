/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:50:48 by alsiavos          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/15 11:29:49 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/07/12 15:43:44 by jpointil         ###   ########.fr       */
>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
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
