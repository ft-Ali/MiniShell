/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/18 11:53:20 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_char(char *s, char c)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s);
	result = (char *)malloc(len + 2);
	if (!result)
	{
		free(s);
		return (NULL);
	}
	ft_strcpy(result, s);
	result[len] = c;
	result[len + 1] = '\0';
	free(s);
	return (result);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

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

static char	*expand_var(t_expand *exp)
{
	char	*result;
	char	*variable_name;
	char	*variable_value;

	if (exp == NULL || exp->input == NULL)
		return (NULL);
	result = ft_strdup("");
	while (exp->input[exp->pos])
	{
		if (exp->input[exp->pos] == '$')
		{
			if (exp->input[exp->pos + 1] && ft_isalpha(exp->input[exp->pos
					+ 1]))
			{
				variable_name = extract_var_name(exp);
				if (variable_name)
				{
					variable_value = getenv(variable_name);
					free(variable_name);
					if (variable_value)
						result = strjoin_free(result, variable_value);
				}
			}
			else
				exp->pos++;
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
		free(token->word);
		token->word = exp.output;
		token = token->next;
	}
}
