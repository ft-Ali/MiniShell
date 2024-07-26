/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/26 11:51:38 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir *add_redir_node(t_token token, char *file)
{
	t_redir	*redir;

	redir = NULL;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		//gestion erreur : free lex, free cmd;
	redir->file = ft_strdup(file);
	redir->token = token;
	redir->next = NULL;
}

// void	add_cmd_node(t_cmd *cmd, char **, char flag)
// {
// 	// oui
// }

void	lex_loop(t_lex *lex, t_cmd *prev, t_cmd *cmd)
{
	while (lex)
	{
		if (lex->token == WORD)
		{
			cmd->commands[i] = ft_strdup(lexer->word);
			if (!cmd->commands[i])
				// secu
				i++;
		}
		else if (lex->token == PIPE)
		{
			cmd->commands[i] = NULL;
			cmd->next = rec_parse(lex->next, cmd, NULL, 0);
		}
		else
		{
			cmd->redir = add_redir_node(lex->token, lex->next->word);
			lex = lex->next;
			cmd->redir = cmd->redir->next;
		}
		lex = lex->next;
	}
	cmd->next = NULL;
	cmd->command[i] = NULL;
}

t_cmd	*rec_parse(t_lex *lex, t_cmd *prev, t_cmd *cmd)
{
	if (!lex)
		return (cmd);
	cmd = ft_calloc(sizeof(t_cmd));
	if (!cmd)
		// gestion erreur : free lex, cmd;
	cmd->commands = calloc(1, sizeof(char));
	if (!cmd->commands)
		//gestion erreur : free lex, cmd;
	cmd->redir = calloc(1, sizeof(t_redir));
	if (!cmd->redir)
		//gestion erreur : free lex, cmd;
	cmd->prev = prev;
	lex_loop(lex, prev, cmd);
}

void	parser(t_shell *shell, t_lex *lex)
{
	shell.cmd = rec_parse(lex, NULL, NULL, 0);
	// free(lex);
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

*/