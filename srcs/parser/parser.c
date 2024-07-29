/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/29 17:09:26 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fonction pour ajouter un nœud de redirection
t_redir *add_redir_node(t_token token, char *file)
{
    t_redir *redir;

    redir = ft_calloc(1, sizeof(t_redir));
    if (!redir)
    {
        perror("Allocation failed");
        return NULL;
    }
    redir->file = ft_strdup(file);
    redir->token = token;
    redir->next = NULL;
    return redir;
}




// Fonction pour traiter les tokens lexicaux et remplir les commandes et redirections
void lex_loop(t_lex *lex, t_cmd *cmd, char **commands)
{
    t_redir *redir_tail = NULL;

    while (lex)
    {
        if (lex->token == WORD)
        {
            // Si des commandes existent déjà, ajoutez le mot comme un argument
            if (*commands && **commands)
            {
                char *temp = ft_strjoin(*commands, " ");
                free(*commands);
                *commands = ft_strjoin(temp, lex->word);
                free(temp);
            }
            else
            {
                *commands = ft_strdup(lex->word);
            }
        }
        else if (lex->token == PIPE)
        {
            // Finalisez la commande actuelle
            if (*commands && **commands)
            {
                cmd->commands = ft_split(*commands, ' ');
                free(*commands);
                *commands = NULL;
            }
            else
            {
                cmd->commands = ft_calloc(1, sizeof(char *));
            }
            
            // Passez à la commande suivante après le pipe
            cmd->next = rec_parse(lex->next, cmd, NULL);
            return;
        }
        else
        {
            // Ajout des redirections
            t_redir *redir = add_redir_node(lex->token, lex->next->word);
            if (!redir)
            {
                perror("Allocation failed");
                return;
            }
            if (!cmd->redir)
            {
                cmd->redir = redir;
                redir_tail = redir;
            }
            else
            {
                redir_tail->next = redir;
                redir_tail = redir;
            }
            lex = lex->next; // Skip the file name token
        }
        lex = lex->next;
    }
    // Finalisez la dernière commande
    if (*commands && **commands)
    {
        cmd->commands = ft_split(*commands, ' ');
    }
    else
    {
        cmd->commands = ft_calloc(1, sizeof(char *));
    }
    free(*commands);
}

// Fonction récursive pour créer les commandes et les redirections
t_cmd *rec_parse(t_lex *lex, t_cmd *prev, t_cmd *cmd)
{
    char *commands;

    if (!lex)
        return NULL;

    cmd = ft_calloc(1, sizeof(t_cmd));
    if (!cmd)
    {
        perror("Allocation failed");
        return NULL;
    }
    cmd->prev = prev;

    commands = ft_strdup("");
    if (!commands)
    {
        perror("Allocation failed");
        free(cmd);
        return NULL;
    }

    lex_loop(lex, cmd, &commands);

    return cmd;
}




// Fonction principale du parser
void parser(t_shell *shell, t_lex *lex)
{
    shell->cmd = rec_parse(lex, NULL, NULL);
    // print_parser(shell->cmd);
}

/*fonctionnement rec parse :

-prend la t_cmd verifie si lex et initialise un premier noeud.
parcours de lex :

check pour chaque noeud de lex le token :
-si word ajoute a l'index du tableau command
-sinon si pipe termine le tableau command, la liste redir,
et relance la ft avec le nouveau noeud
-sinon ajoute le noeud token a la liste redir
---fin de lex

fin de fonction :

-ferme le dernier tableau command
-mets le next du maillon a NULL
renvoie le noeud actuel

allocations :
t_cmd :
-allouer le noeud (calloc)
commands :
-calloc le tab de commands de la taille d'un char
-calloc la command
-avant de joinfree mettre le dernier char a '\n' pour le split
-a chaque rajout strjoin_free avec la new command
-commands = split bigline avec \n
t_redir :
-calloc t_redir
-strdup de lex->next->word dans file
-redir->next = NULL;

FREE CMD :
-ft qui check si on a une commands et une redir
-free ce qui doit etre free
-fais tous les maillons de cmd
*/