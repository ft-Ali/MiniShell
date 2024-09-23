/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:06:07 by jules             #+#    #+#             */
/*   Updated: 2024/09/23 16:53:39 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	handle_identifier(t_env *env, char *arg, t_shell *shell)
{
	trim_spaces(arg);
	if (is_valid_identifier(arg))
		add_or_update_env(&env, arg, "", shell);
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

void	handle_assignment(t_env *env, char *arg, char *equal_sign,
		t_shell *shell)
{
	trim_spaces(arg);
	trim_spaces(equal_sign + 1);
	if (is_valid_identifier(arg))
		add_or_update_env(&env, arg, equal_sign + 1, shell);
	else
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
}

bool	process_arg(t_env *env, char *arg, char *next_arg, t_shell *shell)
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
		handle_assignment(env, arg, equal_sign, shell);
		*equal_sign = '=';
	}
	else
		handle_identifier(env, arg, shell);
	return (free_joined(joined_arg), skip_next);
}

void	bi_export(t_shell *shell, t_cmd *cmd)
{
	bool	skip;
	int		i;

	if (!cmd->commands[1])
		return ;
	i = 1;
	while (cmd->commands[i])
	{
		skip = process_arg(shell->env, cmd->commands[i], cmd->commands[i + 1],
				shell);
		if (skip)
			i++;
		i++;
	}
}
