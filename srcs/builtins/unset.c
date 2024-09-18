/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:04:31 by jules             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/18 13:49:56 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/09/18 13:50:22 by jules            ###   ########.fr       */
>>>>>>> 1276e7b7fbc181a142a9ab839bf275f8c4da7cb9
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    bi_unset(t_shell *shell, t_cmd * cmd)
{
	int		i;
	t_env	*env;

	i = 1;
	if (cmd->prev || cmd->next || !cmd->commands[1])
		return ;
	while (cmd->commands[i])
	{
		env = shell->env;
		while (env)
		{
			if (ft_strictcmp(env->key, cmd->commands[i]))
			{
				if (env->value)
					free(env->value);
				env->value = NULL;
				env->isunset = true;
			}
			env = env->next;
		}
		i++;
	}
	load_env(shell, NULL);
}