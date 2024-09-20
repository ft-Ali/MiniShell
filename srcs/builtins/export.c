/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:06:07 by jules             #+#    #+#             */
/*   Updated: 2024/09/20 16:13:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_or_update_env(t_env *env, const char *key, const char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		exit_shell(NULL, "Error: malloc failed");
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = env;
	if (env)
		env->prev = new_node;
	env = new_node;
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	trim_spaces(char *str)
{
	char	*start;
	char	*end;

	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	if (start != str)
	{
		while (*start)
			*str++ = *start++;
		*str = '\0';
	}
}

void	handle_identifier(t_env *env, char *arg)
{
	trim_spaces(arg);
	if (is_valid_identifier(arg))
		add_or_update_env(env, arg, "");
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

void	free_joined(char *str)
{
	if (str)
		free(str);
}

void	handle_assignment(t_env *env, char *arg, char *equal_sign)
{
	trim_spaces(arg);
	trim_spaces(equal_sign + 1);
	if (is_valid_identifier(arg))
		add_or_update_env(env, arg, equal_sign + 1);
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

bool	process_arg(t_env *env, char *arg, char *next_arg)
{
	char	*equal_sign;
	char	*joined_arg;
	bool	skip_next;

	skip_next = false;
	joined_arg = NULL;
	trim_spaces(arg);
	if (arg && arg[ft_strlen(arg) - 1] == '=' && next_arg)
	{
		joined_arg = ft_strjoin(arg, next_arg);
		if (!joined_arg)
			return (ft_putstr_fd("Error: malloc\n", STDERR_FILENO), false);
		arg = joined_arg;
		skip_next = true;
	}
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		handle_assignment(env, arg, equal_sign);
		*equal_sign = '=';
	}
	else
		handle_identifier(env, arg);
	return (free_joined(joined_arg), skip_next);
}

void	bi_export(t_shell *shell, t_cmd *cmd)
{
	bool skip;
	int i;

	if (!cmd->commands[1])
		return ;
	i = 1;
	while (cmd->commands[i])
	{
		skip = process_arg(shell->env, cmd->commands[i], cmd->commands[i + 1]);
		if (skip)
			i++;
		i++;
	}
}
