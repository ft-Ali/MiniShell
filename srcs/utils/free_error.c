/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:44:58 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/19 11:51:17 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	free(env);
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
		free_cmd(shell->cmd);
	//free(shell);
}

void	gfree(void *ptr, t_struct flag)
{
	if (S)
		(free_shell(ptr), printf("Error : shell"));
	if (L)
		(free_lex(ptr), printf("Error : lexer"));
	if (flag == C)
		(free_cmd(ptr), printf("Error : cmd"));
	if (flag == E)
		(free_exp(ptr), printf("Error : expander"));
	if (flag == P)
		(free_path(ptr), printf("Error : path"));
	if (flag == EN)
		(free_env(ptr), printf("Error : env"));
}

// void	gfree_error(t_flag flag, ...)
// {
// 	va_list ptrs;

// 	va_start(ptrs, flag);
// 	while ((ptr = va_arg(ptrs, void *)) != NULL)
// 	{
// 		if (flag == P)
// 		{
// 			free_cmd(ptr)//premier pointeur
// 			free_lex(ptr)//deuxieme pointeur
// 			printf("Error : parser");
// 		}
// 		if (flag == L)
// 			(free_lex(ptr), printf("Error : lexer"));
// 		if (flag == C)
// 			(free_cmd(ptr), printf("Error : cmd"));
// 		if (flag == E)
// 			(free_exp(ptr), printf("Error : expander"));
// 		if (flag == P)
// 			(free_path(ptr), printf("Error : path"));
// 		if (flag == EN)
// 			(free_env(ptr), printf("Error : env"));
// 	}
// }

/*mettre toutes les fonctions associees avec autre fihier si il faut*/