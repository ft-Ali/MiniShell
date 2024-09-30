/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:19:27 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/30 14:36:17 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	invert_quote(t_lex *lex, int flag, int i, char quote)
{
	t_lex	*tmp;

	tmp = lex;
    i = 0;
	while (tmp)
	{
		while (tmp->word[i])
		{
			if ((tmp->word[i] == '\"' || tmp->word[i] == '\'') && (!flag))
			{
				quote = tmp->word[i];
				flag = 1;
			}
			else if (flag && tmp->word[i] != quote && tmp->word[i] > 0)
				tmp->word[i] *= -1;
			else if (flag == 1 && tmp->word[i] == quote)
			{
				flag = 0;
				quote = '\0';
			}
            i++;
		}
		tmp = tmp->next;
	}
    lex = tmp;
}

void	re_invert_quote(t_lex *lex, int i)
{
	while (lex->word[i])
	{
		if (lex->word[i] < 0)
			lex->word[i] *= -1;
		i++;
	}
}

void	trimquotes(t_lex *lex, int i, int j, t_lex *tmp)
{
	while (lex)
	{
		// tmp->word = ft_calloc(ft_strlen(lex->word) + 1, sizeof(char));
		// if (!tmp->word)
		// 	return (NULL);
        invert_quote(lex, 0, -1, '\0');
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
        re_invert_quote(tmp, 0);
		lex = lex->next;
		tmp = tmp->next;
	}
    lex = tmp;
	return ;
}
