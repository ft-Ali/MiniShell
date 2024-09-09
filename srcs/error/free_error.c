/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:44:58 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/09 10:18:08 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_path(t_path *path)
{
    if (path->path_str)
        free_str(path->path_str);
    if (path->next)
        free_path(path->next);
    free(path);
}

void free_lex(t_lex *lex)
{
    if (lex->word)
        free_str(lex->word);
    if (lex->token)
        free(lex->token);
    if (lex->next)
        free_lex(lex->next);
    free(lex);
}

void free_env(t_env *env)
{
    if (env->value)
        free_str(env->value)
    if (env->key)
        free_str(env->key);
    if (env->index)
        free(env->index);
    if (env->next)
        free_env(env->next);
    if (env->prev)
        free_env(env->prev);
    free(env);
}

void    free_shell(t_shell *shell)
{
    if (shell->env)
        free_env(shell->env);
    if (shell->lex)
        free_lex(shell->lex);
    if (shell->path)
        free_path(shell->path);
    if (shell->cmd)
        free_cmd(shell->cmd);
}

void    global_free_error(void *ptr, t_type struct)
{
    if (type == S)
    {
        free_shell(ptr);//avec error qui suit
    }
    if (type == L)
    {
        free_lex(ptr);//avec error qui suit
    }
    if (type == C)
    {
        free_cmd(ptr);//avec error qui suit
    }
    if (type == E)
    {
        free_exp(ptr);//avec error qui suit
    }
    if (type == P)
    {
        free_path(ptr);//avec error qui suit
    }
    if (type == EN)
    {
        free_env(ptr);//avec error qui suit
    }
}

/*mettre toutes les fonctions associees avec autre fihier si il faut*/