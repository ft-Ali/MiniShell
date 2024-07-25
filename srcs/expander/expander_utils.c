/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/25 14:09:05 by alsiavos         ###   ########.fr       */
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

void	handle_quotes(t_expand *exp, char *quote)
{
	if (exp->input[exp->pos] == '"' || exp->input[exp->pos] == '\'')
	{
		if (*quote == '\0')
		{
			*quote = exp->input[exp->pos];
			ft_memmove(&exp->input[exp->pos], &exp->input[exp->pos + 1],
				ft_strlen(exp->input) - exp->pos);
		}
		else if (*quote == exp->input[exp->pos])
		{
			*quote = '\0';
			ft_memmove(&exp->input[exp->pos], &exp->input[exp->pos + 1],
				ft_strlen(exp->input) - exp->pos);
		}
	}
}

int	handle_variable_expansion(t_expand *exp, char **result, char quote)
{
	char	*variable_name;
	char	*variable_value;
	int		start;

	if (exp->input[exp->pos] == '$' && quote != '\'')
	{
		exp->pos++;
		start = exp->pos;
		while (ft_isdigit(exp->input[exp->pos]))
			exp->pos++;
		if (exp->pos > start)
			return (1);
		while (ft_isalnum(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
			exp->pos++;
		variable_name = ft_strndup(exp->input + start, exp->pos - start);
		variable_value = getenv(variable_name);
		*result = strjoin_free(*result, variable_value);
		free(variable_name);
		return (1);
	}
	return (0);
}
