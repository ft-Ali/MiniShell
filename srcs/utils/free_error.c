/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:44:58 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/26 14:12:27 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->file)
		free(redir->file);
	if (redir->next)
		free_redir(redir->next);
	free(redir);
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	if (!env || !*env)
		return ;
	tmp = *env;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
		tmp = next;
	}
	*env = NULL;
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env(&shell->env);
	if (shell->lex)
		free_lex(shell->lex);
	if (shell->path)
		free_path(shell->path);
	if (shell->cmd)
		free_cmd(shell->cmd);
	if (shell->input)
		free(shell->input);
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