/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/26 20:02:59 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_char(char *result, char *input, int pos)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(input, pos, 1);          // Extract the current character
	joined_result = ft_strjoin(result, temp); // Join it with the result
	free(temp);
	free(result); // Free the old result to avoid memory leak
	return (joined_result);
}

char	*expand_var(char *input, int pos, t_env *env)
{
	char	*result;
	char	quote;
	int		var_len;

	quote = '\0'; // Track if we're inside quotes
	if (input == NULL)
		return (NULL);
	result = ft_strdup(""); // Start with an empty string for the result
	while (pos < (int)ft_strlen(input))
	{
		handle_quotes(input, &pos, &quote);
		// Handle opening/closing of quotes
		var_len = handle_variable_expansion(input + pos, &result, quote, env);
		// Handle variable expansion
		if (var_len > 0) // If a variable was expanded,
		{
			pos += var_len;
			continue ;
		}
		result = expand_char(result, input, pos);
		// Append the current character to the result
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



static char	*trimquotes(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = ft_calloc((ft_strlen(str) - count_char(str) + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	if (new[j] != '\0')
		j++;
	new[j] = '\0';
	return (new);
}



char	*expander(char *input, t_env *env)
{
	char	*expanded_input;
	char	*trimmed_input;

	expanded_input = expand_var(input, 0, env); // Expand variables in the input
	//avant ca mettre les quotes en negatif avec renegquotes
	trimmed_input = trimquotes(expanded_input);                
	free(expanded_input); // Free the expanded input
	return (trimmed_input);
	// Return the fully expanded input
}
