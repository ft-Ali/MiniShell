/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/27 17:50:10 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_char(char *result, char *input, int pos)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(input, pos, 1);
	joined_result = ft_strjoin(result, temp);
	free(temp);
	free(result);
	return (joined_result);
}

char	*expand_var(char *input, int pos, t_env *env)
{
	char	*result;
	char	quote;
	int		var_len;

	quote = '\0';
	if (input == NULL)
		return (NULL);
	result = ft_strdup("");
	while (pos < (int)ft_strlen(input))
	{
		handle_quotes(input, &pos, &quote);
		var_len = handle_variable_expansion(input + pos, &result, quote, env);
		if (var_len > 0)
		{
			pos += var_len;
			continue ;
		}
		result = expand_char(result, input, pos);
		pos++;
	}
	return (result);
}

size_t	count_char(char *str)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c++;
		i++;
	}
	return (c);
}

void	re_invert_quote(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] < 0)
			input[i] *= -1;
		i++;
	}
}

char	*expander(char *input, t_env *env)
{
	char	*expanded_input;
	char	*trimmed_input;

	expanded_input = expand_var(input, 0, env);
	invert_quote(expanded_input);
	trimmed_input = trimquotes(expanded_input);
	re_invert_quote(trimmed_input);
	free(expanded_input);
	return (trimmed_input);
}
