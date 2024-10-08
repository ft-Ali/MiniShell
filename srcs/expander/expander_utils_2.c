/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:09:58 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/03 16:36:46 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_norm(t_norm *norm)
{
	norm->isfree = false;
	norm->variable_value = NULL;
	norm->temp = NULL;
	norm->variable_name = NULL;
	norm->start = 1;
}

char	*expansion_core_util(char *temp, char **result, char *variable_value)
{
	temp = ft_strjoin_free_n(*result, variable_value);
	*result = temp;
	return (*result);
}

int	handle_special_cases(char *input, char **result)
{
	if (input[0] == '$' && (input[1] == '\0' || (!ft_isalnum(input[1])
				&& input[1] != '_' && input[1] != '?')))
	{
		*result = ft_strjoin_free_n(*result, "$");
		return (1);
	}
	return (0);
}

int	handle_variable_expansion_core(char *input, char **result, t_shell *shell,
		t_norm *norm)
{
	while (input[norm->start] && (ft_isalnum(input[norm->start])
			|| input[norm->start] == '_' || input[norm->start] == '?'))
		norm->start++;
	norm->variable_name = ft_substr(input, 1, norm->start - 1);
	if (!norm->variable_name)
		return (0);
	if (input[norm->start - 1] == '?')
	{
		norm->variable_value = ft_itoa(shell->excode);
		norm->isfree = true;
	}
	else
		norm->variable_value = get_custom_env(shell->env, norm->variable_name);
	free(norm->variable_name);
	if (norm->variable_value)
		expansion_core_util(norm->temp, result, norm->variable_value);
	else
	{
		norm->temp = ft_strjoin_free_n(*result, "");
		*result = norm->temp;
	}
	if (norm->variable_value && norm->isfree)
		free(norm->variable_value);
	return (norm->start);
}

int	handle_variable_expansion(char *input, char **result, char quote,
		t_shell *shell)
{
	int		special_case_len;
	t_norm	norm;

	init_norm(&norm);
	if (!input)
		return (0);
	special_case_len = handle_special_cases(input, result);
	if (special_case_len > 0)
		return (special_case_len);
	if (input[0] == '$' && quote != '\'')
		return (handle_variable_expansion_core(input, result, shell, &norm));
	return (0);
}
