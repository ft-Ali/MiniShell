/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:28:49 by jules             #+#    #+#             */
/*   Updated: 2024/09/18 12:34:29 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_pwd(t_shell *shell, t_cmd *cmd)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("pwd: error retrieving current directory: getcwd: \
			cannot access parent directories: No such file or directory");
    
}