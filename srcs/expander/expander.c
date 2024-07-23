/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/23 18:35:39 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*extract_var_name(t_expand *exp)
{
	int		start;
	char	*var_name;

	start = ++exp->pos;
	while (exp->input[exp->pos] && ft_isalnum(exp->input[exp->pos]))
		exp->pos++;
	var_name = ft_strndup(&exp->input[start], exp->pos - start);
	return (var_name);
}

static char	*expand_char(char *result, t_expand *exp)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(exp->input, exp->pos, 1);
	joined_result = strjoin_free(result, temp);
	free(temp);
	return (joined_result);
}

static char *expand_var(t_expand *exp) 
{
	char	*result;
	char	*variable_name;
	char	*variable_value;
	char	quote = '\0';

	if (exp == NULL || exp->input == NULL)
		return (NULL);
	result = ft_strdup("");
	while (exp->input[exp->pos]) 
	{
		if (exp->input[exp->pos] == '"' || exp->input[exp->pos] == '\'') 
		{
			if (quote == '\0') 
			{
				quote = exp->input[exp->pos];
			exp->pos++;
			continue;
			}
			else if (quote == exp->input[exp->pos]) 
			{
				quote = '\0';
				exp->pos++;
				continue;
			}
		}
		if (exp->input[exp->pos] == '$' && quote != '\'') 
		{
			if (exp->input[exp->pos + 1] && ft_isalpha(exp->input[exp->pos + 1])) 
			{
				variable_name = extract_var_name(exp);
				if (variable_name)
				{
					variable_value = getenv(variable_name);
					free(variable_name);
					if (variable_value)
						result = strjoin_free(result, variable_value);
					continue;
				}
			}
		}
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
		ft_printf("exp.output: %s\n", exp.output);
		free(token->word);
		token->word = exp.output;
		token = token->next;
	}
}
