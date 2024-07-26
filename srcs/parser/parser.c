/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/07/26 14:49:52 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*add_redir_node(t_token token, char *file)
{
	t_redir	*redir;

	redir = NULL;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		printf("KO4\n");
	// gestion erreur : free lex, cmd redir;
	redir->file = ft_strdup(file);
	redir->token = token;
	redir->next = NULL;
	return (redir);
}

void	lex_loop(t_lex *lex, char *word, char *commands, t_cmd *cmd)
{
	while (lex)
	{
		if (lex->token == WORD)
		{
			word = ft_strdup(lex->word);
			if (!word)
				printf("KO3\n");
			// erreur : free lex, cmd;
		}
		else if (lex->token == PIPE)
		{
			commands = ft_strjoin_free_n(commands, word);
			cmd->next = rec_parse(lex->next, cmd, NULL);
		}
		else
		{
			cmd->redir = add_redir_node(lex->token, lex->next->word);
			lex = lex->next;
			cmd->redir = cmd->redir->next;
		}
		commands = ft_strjoin_free_n(commands, word);
		printf("%s\n", commands);
		lex = lex->next;
	}
	cmd->next = NULL;
}

t_cmd	*rec_parse(t_lex *lex, t_cmd *prev, t_cmd *cmd)
{
	char	*commands;

	if (!lex)
		return (cmd);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		printf("KO2\n");
	// gestion erreur : free lex, cmd;
	commands = ft_calloc(1, sizeof(char));
	if (!commands)
		printf("KO1\n");
	// gestion erreur : free lex, cmd, commands;
	cmd->prev = prev;
	lex_loop(lex, 0, commands, cmd);
	cmd->commands = ft_split(commands, '\n');
	printf("commands : %s\n", cmd->commands);
	return (cmd);
}

void	parser(t_shell *shell, t_lex *lex)
{
	printf("OK\n");
	shell->cmd = rec_parse(lex, NULL, NULL);
	printf("OK2\n");
	// free(lex);
	print_parser(shell->cmd);
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