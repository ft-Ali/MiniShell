/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/10 09:43:02 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		while (ft_isalpha(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
			exp->pos++;
		variable_name = ft_strndup(exp->input + start, exp->pos - start);
		variable_value = getenv(variable_name);
		*result = strjoin_free(*result, variable_value);
		free(variable_name);
		return (1);
	}
	return (0);
}
