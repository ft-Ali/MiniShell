/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/26 14:55:32 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_char(char *result, t_expand *exp)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(exp->input, exp->pos, 1);
	joined_result = strjoin_free(result, temp);
	free(temp);
	return (joined_result);
}

char	*expand_var(t_expand *exp)
{
	char	*result;
	char	quote;

	quote = '\0';
	if (exp == NULL || exp->input == NULL)
		return (NULL);
	result = ft_strdup("");
	while (exp->pos < (int)ft_strlen(exp->input))
	{
		handle_quotes(exp, &quote);
		if (exp->input[exp->pos] && handle_variable_expansion(exp, &result,
				quote))
			continue ;
		result = expand_char(result, exp);
		exp->pos++;
	}
	return (result);
}

void	expander(t_lex *token)
{
	t_expand	exp;

	while (token)
	{
		exp.input = token->word;
		exp.pos = 0;
		exp.output = expand_var(&exp);
		free(token->word);
		token->word = exp.output;
		token = token->next;
	}
}
