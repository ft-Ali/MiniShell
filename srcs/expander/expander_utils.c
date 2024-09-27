/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 13:40:08 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/27 17:31:40 by jpointil         ###   ########.fr       */
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

// int	handle_variable_expansion(char *input, char **result, char quote,
// 		t_env *env)
// {
// 	char	*variable_name;
// 	char	*variable_value;
// 	int		start;
// 	char	*temp;

// 	start = 1;
// 	if (!input)
// 		return (0);
//    else if (input[0] == '$' && (input[1] == '\0' || (!ft_isalnum(input[1])
// && input[1] != '_')))
//     {
//         *result = ft_strjoin_free_n(*result, "$");
//         return (1);
//     }
//     else if (input[0] == '$' && quote != '\'')
//     {
//         while (input[start] && (ft_isalnum(input[start])
// || input[start] == '_'))
//             start++;
//         variable_name = ft_substr(input, 1, start - 1);
//         variable_value = get_custom_env(env, variable_name);
//         free(variable_name);
//         if (variable_value)
//         {
//             temp = ft_strjoin(*result, variable_value);
//             free(*result);
//             *result = temp;
//         }
//         else
//         {
//             temp = ft_strjoin_free_n(*result, "");
//             *result = temp;
//         }
//         return (start);
//     }
// 	return (0);
// }
