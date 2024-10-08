/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/03 16:36:12 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_char(char *result, char *input, int pos)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(input, pos, 1);
	joined_result = ft_strjoin(result, temp);
	if (!joined_result)
	{
		free(temp);
		free(result);
		return (NULL);
	}
	free(temp);
	free(result);
	return (joined_result);
}

char	*expand_var(char *input, int pos, t_shell *shell)
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
		var_len = handle_variable_expansion(input + pos, &result, quote, shell);
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

char	*expander(char *input, t_shell *shell)
{
	char	*expanded_input;

	if (ft_strictcmp(input, "\"\"") || ft_strictcmp(input, "''"))
	{
		shell->excode = 127;
		printf("%s: command not found\n", input);
		return (NULL);
	}
	expanded_input = expand_var(input, 0, shell);
	if (!expanded_input)
		return (NULL);
	return (expanded_input);
}
