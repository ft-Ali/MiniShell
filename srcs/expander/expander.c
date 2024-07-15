/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:13:43 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/16 00:01:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *ft_strjoinchar(char *s, char c)
{
    size_t len = strlen(s);
    char *result = (char *)malloc(len + 2);
    if (!result)
    {
        free(s);
        return NULL;
	}
    strcpy(result, s); 
    result[len] = c;
    result[len + 1] = '\0'; 

    free(s);
    return result;
}

char	*strjoinfree(char *s1, char *s2)
{
	char	*new_str;

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static char	*extract_var_name(t_expand *exp)
{
	int		start;
	char	*var_name;

	start = ++exp->pos;
	while (exp->input[exp->pos] && ft_isalnum(exp->input[exp->pos]))
		exp->pos++;
	var_name = ft_strndup(&exp->input[start], exp->pos - start);
	exp->pos--;
	return (var_name);
}

static char	*expand_char(char *result, t_expand *exp)
{
	char	*temp;
	char	*joined_result;

	temp = ft_substr(exp->input, exp->pos, 1);
	joined_result = ft_strjoin(result, temp);
	free(result);
	free(temp);
	return (joined_result);
}

static char	*expand_var(t_expand *exp)
{
	char	*result;
	char	*variable_name;
	char	*variable_value;
	char	*temp;

	// ft_printf("INPUT2 [%s]\n", exp->input);
	
	if (exp == NULL || exp->input == NULL)
        	return NULL;
	result = ft_strdup("");
	while (exp->input[exp->pos])
	{
		if (exp->input[exp->pos] == '$')
		{
			variable_name = extract_var_name(exp);
			if (variable_name)
			{
				variable_value = getenv(variable_name);
				free(variable_name);
				if (variable_value)
				{
					temp = ft_strjoin(result, variable_value);
					free(result);
					result = temp;
				}
			}
		}
		else
			result = expand_char(result, exp);
		exp->pos++;
	}
	
	return (result);
}
void	expander(t_lex *token)
{
	t_expand	exp;

	while (token)
	{
		ft_printf("INPUT4 [%s]\n", exp.input);
		exp.input = token->word;
		exp.pos = 0;
		exp.output = expand_var(&exp);
		free(token->word);
		token->word = exp.output;
		// ft_printf("INPUT3 [%s]\n", exp.output);
		token = token->next;
	}
}
