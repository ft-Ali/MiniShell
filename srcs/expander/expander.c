/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:21:43 by alsiavos          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/15 11:41:58 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/07/12 14:27:20 by alsiavos         ###   ########.fr       */
>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*strjoinfree(char *s1, char *s2)
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
	exp->pos--;
	return (var_name);
}

static char	*expand_char(char *result, t_expand *exp)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(exp->input, exp->pos, 1);
	joined_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (joined_result);
}

static char	*expand_var(t_expand *exp)
{
	char	*result;
	char	*variable_name;
	char	*variable_value;
	char	*temp;

	result = ft_strdup("");
	while (exp->input[exp->pos])
	{
		if (exp->input[exp->pos] == '$')
		{
			variable_name = extract_var_name(exp);
			if (variable_name)
			{
				variable_value = getenv(variable_name);
				free(variable_name);
				if (variable_value)
				{
					temp = ft_strjoin(result, variable_value);
					free(result);
					result = temp;
				}
			}
		}
		else
			result = expand_char(result, exp);
		exp->pos++;
	}
	return (result);
}
void	expander(t_lexer *token)
{
	t_expand	exp;

	while (token)
	{
		exp.input = token->str;
		exp.pos = 0;
		exp.output = expand_var(&exp);
		free(token->str);
		token->str = exp.output;
		token = token->next;
	}
}
