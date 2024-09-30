/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:19:27 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/30 17:24:01 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*invert_quote(char *word, int flag, int i)
{
	char	quote;

	if (!word)
		return (NULL);
	while (word[i])
	{
		if ((word[i] == '\"' || word[i] == '\'') && (!flag))
		{
			quote = word[i];
			flag = 1;
		}
		else if (flag && word[i] != quote && word[i] > 0)
			word[i] *= -1;
		else if (flag == 1 && word[i] == quote)
			flag = 0;
		i++;
	}
	return (word);
}

char	*re_invert_quote(char *word, int i)
{
	while (word[i])
	{
		if (word[i] < 0)
			word[i] *= -1;
		i++;
	}
	return (word);
}

char	*trimquotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc((ft_strlen(str) - count_char(str) + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	if (new[j] != '\0')
		j++;
	new[j] = '\0';
	free(str);
	return (new);
}

t_lex	*trimquote_process(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->word)
		{
			tmp->word = invert_quote(tmp->word, 0, 0);
			tmp->word = trimquotes(tmp->word);
			if (!tmp->word)
				return (NULL);
			tmp->word = re_invert_quote(tmp->word, 0);
		}
		tmp = tmp->next;
	}
	return (lex);
}
