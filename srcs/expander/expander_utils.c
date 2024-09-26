/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 19:44:06 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_quotes(char *input, int *pos, char *quote)
{
	if (input[*pos] == '\'' && *quote != '"')
	{
		if (*quote == '\'')
			*quote = '\0';
		else
			*quote = '\'';
	}
	else if (input[*pos] == '"' && *quote != '\'')
	{
		if (*quote == '"')
			*quote = '\0';
		else
			*quote = '"';
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

int	handle_variable_expansion(char *input, char **result, char quote, t_env *env)
{
	char	*variable_name;
	char	*variable_value;
	int		start;
	char	*temp;

	// Only expand variables if not inside single quotes
	if (input[0] == '$' && quote != '\'')
	{
		start = 1;
		while (input[start] && (ft_isalnum(input[start]) || input[start] == '_'))
			start++;
		variable_name = ft_substr(input, 1, start - 1);  // Extract variable name after '$'
		variable_value = get_custom_env(env, variable_name);
		free(variable_name);

		if (variable_value)
		{
			temp = ft_strjoin(*result, variable_value);  // Join the expanded variable value to result
			free(*result);
			*result = temp;
		}
		return (start);  // Return the length of the variable name (to adjust position in the main loop)
	}
	return (0);
}
