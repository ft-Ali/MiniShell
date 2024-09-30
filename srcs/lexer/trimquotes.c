/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:19:27 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/30 12:31:28 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	invert_quote(t_lex *lex, int flag, int i, char quote)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		while (input[++i])
		{
			if ((input[i] == '\"' || input[i] == '\'') && (!flag))
			{
				quote = input[i];
				flag = 1;
			}
			else if (flag && input[i] != quote && input[i] > 0)
				input[i] *= -1;
			else if (flag == 1 && input[i] == quote)
			{
				flag = 0;
				quote = '\0';
			}
		}
		tmp = tmp->next;
	}
}

void	re_invert_quote(t_lex *lex, int i)
{
	while (input[i])
	{
		if (input[i] < 0)
			input[i] *= -1;
		i++;
	}
}

void	trimquote(t_lex *lex, int i, int j, t_lex *tmp)
{
	invert_quote(lex, 0, -1, '\0');
    while (lex)
    {
        tmp->word = ft_calloc(ft_strlen(lex->word) + 1, sizeof(char));
	    if (!tmp->word)
		    return (NULL);
	    while (lex->word[i])
	    {
	    	if (lex->word[i] != '\'' && lex->word[i] != '\"')
		    {
		    	tmp->word[j] = lex->word[i];
		    	j++;
		    }
		    i++;
	    }
	    tmp->word[j] = '\0';
        lex = lex->next;
        tmp = tmp->next;
    }
	re_invert_quote(lex, 0);
	return ;
}
