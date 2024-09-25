/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/25 15:39:54 by alsiavos         ###   ########.fr       */
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

char	*get_custom_env(t_env *env, char *var_name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var_name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	handle_variable_expansion(t_expand *exp, char **result, char quote,
		t_env *env)
{
	char	*variable_name;
	char	*variable_value;
	int		start;

	if(exp->input[exp->pos] == '$')
	{
		*result = ft_strjoin_free_n(*result, "$");
		exp->pos++;
		return (1);	
	}
	if (exp->input[exp->pos] == '$' && quote != '\'')
	{
		exp->pos++;
		start = exp->pos;
		while (ft_isdigit(exp->input[exp->pos])
			|| ft_isalpha(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
			exp->pos++;
		variable_name = ft_strndup(exp->input + start, exp->pos - start);
		variable_value = get_custom_env(env, variable_name);
		*result = ft_strjoin_free_n(*result, variable_value);
		free(variable_name);
		return (1);
	}
	return (0);
}
