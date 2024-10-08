/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:05:50 by jpointil          #+#    #+#             */
/*   Updated: 2024/10/03 14:04:30 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cmp_llmax(const char *str, long long value, int sign)
{
	int	digit;

	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		digit = *str - '0';
		if (value > (LLONG_MAX - digit) / 10)
			return (0);
		value = value * 10 + digit;
		str++;
	}
	value *= sign;
	if (value < LLONG_MIN || value > LLONG_MAX)
		return (0);
	return (1);
}

static int	check_long(const char *str)
{
	long long	value;
	int			sign;

	value = 0;
	if (*str == '\0')
		return (0);
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str == '\0')
		return (0);
	return (cmp_llmax(str, value, sign));
}

int	exit_options(t_cmd *cmd, int *flag)
{
	int	i;

	i = 0;
	if (!check_long(cmd->commands[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->commands[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		(*flag) = 1;
		return (2);
	}
	return (ft_atoi(cmd->commands[1]) % 256);
}

void	bi_exit(t_shell *shell, t_cmd *cmd)
{
	int	ext;
	int	flag;

	flag = 0;
	if (cmd->commands[1])
		shell->tmpexcode = exit_options(cmd, &flag);
	if (cmd->commands[1] && cmd->commands[2] && !flag)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		ft_putstr_fd("exit\n", 1);
		shell->excode = 1;
		shell->tmpexcode = 1;
		return ;
	}
	if (cmd->next || cmd->prev)
		return ;
	ext = shell->tmpexcode;
	free_shell(shell);
	ft_putstr_fd("exit\n", 1);
	exit(ext);
}
