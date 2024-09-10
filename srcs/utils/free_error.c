/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:44:58 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/10 09:47:57 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	if (!env)
		return ;
	if (env->value)
		free(env->value);
	if (env->key)
		free(env->key);
	if (env->next)
		free_env(env->next);
	free(env)
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env(shell->env);
	if (shell->lex)
		free_lex(shell->lex);
	if (shell->path)
		free_path(shell->path);
	if (shell->cmd)
		free_cmd(shell->cmd)
}

void	gfree_error(void *ptr, t_type type)
{
	if (type == S)
		(free_shell(ptr), printf("Error : shell"));
	if (type == L)
		(free_lex(ptr), printf("Error : lexer"));
	if (type == C)
		(free_cmd(ptr), printf("Error : cmd"));
	if (type == E)
		(free_exp(ptr), printf("Error : expander"));
	if (type == P)
		(free_path(ptr), printf("Error : path"));
	if (type == EN)
		(free_env(ptr), printf("Error : env"));
}

/*mettre toutes les fonctions associees avec autre fihier si il faut*/