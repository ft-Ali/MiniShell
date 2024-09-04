/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:44:58 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/04 23:06:35 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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