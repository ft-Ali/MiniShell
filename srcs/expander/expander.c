/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/27 16:08:31 by alsiavos         ###   ########.fr       */
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

char *expand_var(char *input, int pos, t_env *env)
{
    char    *result;
    char    quote;
    int     var_len;

    quote = '\0';  // Track if we're inside quotes
    if (input == NULL)
        return (NULL);
    result = ft_strdup("");  // Start with an empty string for the result

    while (pos < (int)ft_strlen(input))
    {
        handle_quotes(input, &pos, &quote);  // Handle opening/closing of quotes
        // Skip variable expansion inside single quotes
        var_len = handle_variable_expansion(input + pos, &result, quote, env);
        if (var_len > 0)
        {
            pos += var_len;  // Skip over the expanded variable
            continue;
        }
        result = expand_char(result, input, pos);  // Append current char to result
        pos++;
    }
    return (result);  // Return the expanded string with quotes preserved
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

void renegentrecote(char *input)
{
    int     flag = 0;
    char    quote = '\0';
    int     i = -1;

    while (input[++i])
    {
        // Detect opening quotes
        if ((input[i] == '\"' || input[i] == '\'') && (!flag))
        {
            quote = input[i];  // Set active quote type
            flag = 1;
        }
        // Inside quotes, mark characters as non-expandable (negative ASCII)
        else if (flag && input[i] != quote && input[i] > 0)
            input[i] *= -1;  // Mark non-expandable
        // Detect closing quotes and stop marking
        else if (flag == 1 && input[i] == quote)
        {
            flag = 0;
            quote = '\0';  // Reset quote
        }
    }
}

void backtoascii(char *input)
{
    int i = 0;

    while (input[i])
    {
        if (input[i] < 0)  // If marked as non-expandable, restore to positive ASCII
            input[i] *= -1;
        i++;
    }
}

char *trimquotes(char *str)
{
    char    *new;
    int     i = 0;
    int     j = 0;

    // Allocate space for the new string, skipping unnecessary quotes
    new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
    if (!new)
        return (NULL);
    while (str[i])
    {
        // Skip quotes
        if (str[i] != '\'' && str[i] != '\"')
        {
            new[j] = str[i];  // Copy characters excluding quotes
            j++;
        }
        i++;
    }
    new[j] = '\0';  // Null-terminate the new string
    return (new);
}

char *expander(char *input, t_env *env)
{
    char *expanded_input;
    char *trimmed_input;

    // Step 1: Expand variables in the input
    expanded_input = expand_var(input, 0, env);

    // Step 2: Mark characters inside quotes as non-expandable
    renegentrecote(expanded_input);

    // Step 3: Trim unnecessary quotes, preserving needed ones
    trimmed_input = trimquotes(expanded_input);

    // Step 4: Restore marked characters inside single quotes
    backtoascii(trimmed_input);

    free(expanded_input);  // Free the expanded input string
    return (trimmed_input);  // Return the fully processed string ready for lexer
}
