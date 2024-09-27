/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:09:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/27 17:32:08 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fonction pour gérer les cas spéciaux comme $ seul ou $?
int	handle_special_cases(char *input, char **result)
{
	if (input[0] == '$' && (input[1] == '\0' || (!ft_isalnum(input[1])
				&& input[1] != '_')))
	{
		*result = ft_strjoin_free_n(*result, "$");
		return (1);
	}
	return (0);
}

// Fonction pour gérer l'expansion des variables
int	handle_variable_expansion_core(char *input, char **result, t_env *env)
{
	char	*variable_name;
	char	*variable_value;
	char	*temp;
	int		start;

	start = 1;
	while (input[start] && (ft_isalnum(input[start]) || input[start] == '_'))
		start++;
	variable_name = ft_substr(input, 1, start - 1);
	variable_value = get_custom_env(env, variable_name);
	free(variable_name);
	if (variable_value)
	{
		temp = ft_strjoin(*result, variable_value);
		free(*result);
		*result = temp;
	}
	else
	{
		temp = ft_strjoin_free_n(*result, "");
		*result = temp;
	}
	return (start);
}

// Fonction principale pour gérer l'expansion des variables
int	handle_variable_expansion(char *input, char **result, char quote,
		t_env *env)
{
	int	special_case_len;

	if (!input)
		return (0);
	special_case_len = handle_special_cases(input, result);
	if (special_case_len > 0)
		return (special_case_len);
	if (input[0] == '$' && quote != '\'')
		return (handle_variable_expansion_core(input, result, env));
	return (0);
}
