/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 13:41:40 by jpointil         ###   ########.fr       */
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

// 1ER
// int	handle_variable_expansion(t_expand *exp, char **result, char quote,
// 		t_env *env)
// {
// 	char	*variable_name;
// 	char	*variable_value;
// 	int		start;

// 	if (exp->input[exp->pos] == '$' && quote != '\'')
// 	{
// 		exp->pos++;
// 		if (exp->input[exp->pos] == '\0' || ft_isspace(exp->input[exp->pos]))
// 		{
// 			*result = ft_strjoin_free_n(*result, "$");
// 			return (1);
// 		}
// 		start = exp->pos;
// 		while (ft_isdigit(exp->input[exp->pos])
// 			|| ft_isalpha(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
// 			exp->pos++;
// 		variable_name = ft_strndup(exp->input + start, exp->pos - start);
// 		variable_value = get_custom_env(env, variable_name);
// 		if (variable_value)
// 			*result = ft_strjoin_free_n(*result, variable_value);
// 		free(variable_name);
// 		return (1);
// 	}
// 	return (0);
// }

// 2EME
// int	handle_variable_expansion(t_expand *exp, char **result, char quote,
// 		t_env *env)
// {
// 	char	*variable_name;
// 	char	*variable_value;
// 	int		start;

// 	if (exp->input[exp->pos] == '$' && (quote != '\'' || quote != '\"'))
// 	{
// 		exp->pos++;
// 		if (exp->input[exp->pos] == '\0' || (!ft_isalnum(exp->input[exp->pos])
// 				&& exp->input[exp->pos] != '_'))
// 		{
// 			*result = ft_strjoin_free_n(*result, "$");
// 			return (1);
// 		}
// 		start = exp->pos;
// 		while (ft_isdigit(exp->input[exp->pos])
// 			|| ft_isalpha(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
// 			exp->pos++;
// 		variable_name = ft_strndup(exp->input + start, exp->pos - start);
// 		variable_value = get_custom_env(env, variable_name);
// 		if (variable_value)
// 			*result = ft_strjoin_free_n(*result, variable_value);
// 		free(variable_name);
// 		return (1);
// 	}
// 	return (0);
// }

// 3EME
int	handle_variable_expansion(t_expand *exp, char **result, char quote,
		t_env *env)
{
	char	*variable_name;
	char	*variable_value;
	int		start;

	if (exp->input[exp->pos] == '$' && quote != '\'')
	{
		exp->pos++;
		if (exp->input[exp->pos] == '\0' || (!ft_isalnum(exp->input[exp->pos])
				&& exp->input[exp->pos] != '_'))
			return (*result = ft_strjoin_free_n(*result, "$"), 1);
		start = exp->pos;
		while (ft_isalnum(exp->input[exp->pos]) || exp->input[exp->pos] == '_')
			exp->pos++;
		variable_name = ft_strndup(exp->input + start, exp->pos - start);
		variable_value = get_custom_env(env, variable_name);
		if (variable_value)
			*result = ft_strjoin_free_n(*result, variable_value);
		else
			*result = ft_strjoin_free_n(*result, "");
		free(variable_name);
		return (1);
	}
	return (0);
}
