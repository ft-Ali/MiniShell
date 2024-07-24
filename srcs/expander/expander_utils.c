/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/24 14:02:35 by alsiavos         ###   ########.fr       */
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
	if (exp->input[exp->pos] == '\0')
		return ;
	if (exp->input[exp->pos] == '"' || exp->input[exp->pos] == '\'')
	{
		if (*quote == '\0')
		{
			*quote = exp->input[exp->pos];
			exp->pos++;
		}
		else if (*quote == exp->input[exp->pos])
		{
			*quote = '\0';
			exp->pos++;
		}
	}
}

int	handle_variable_expansion(t_expand *exp, char **result, char quote)
{
	char	*variable_name;
	char	*variable_value;

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
					*result = strjoin_free(*result, variable_value);
				return (1);
			}
		}
	}
	return (0);
}
