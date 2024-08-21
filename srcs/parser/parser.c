/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/08/21 11:48:27 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Fonction pour ajouter un nœud de redirection

t_redir	*add_redir_node(t_token token, char *file)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
	{
		perror("Allocation failed");
		return (NULL);
	}
	redir->token = token;
	redir->file = strdup(file);
	redir->next = NULL;
	return (redir);
}

// Fonction pour traiter les tokens lexicaux et remplir les commandes et redirections
void	handle_redirections(t_lex **lex, t_cmd *cmd, t_redir **redir_tail)
{
	t_redir	*redir;

	redir = add_redir_node((*lex)->token, (*lex)->next->word);
	if (!cmd->redir)
		cmd->redir = redir;
	else
		(*redir_tail)->next = redir;
	*redir_tail = redir;
	*lex = (*lex)->next; // Skip the file name token
}

void	append_command(t_cmd *cmd, char *word)
{
	int		i;
	char	**new_commands;

	i = 0;
	while (cmd->commands && cmd->commands[i])
		i++;
	new_commands = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_commands)
	{
		perror("Allocation failed");
		return ;
	}
	i = 0;
	while (cmd->commands && cmd->commands[i])
	{
		new_commands[i] = cmd->commands[i];
		i++;
	}
	new_commands[i] = strdup(word);
	new_commands[i + 1] = NULL;
	if (cmd->commands)
		free(cmd->commands);
	cmd->commands = new_commands;
}

void	lex_loop(t_lex *lex, t_cmd *cmd)
{
	t_redir	*redir_tail;

	redir_tail = NULL;
	while (lex)
	{
		if (lex->token == WORD)
			append_command(cmd, lex->word);
		else if (lex->token == PIPE)
		{
			if (cmd->commands)
			{
				cmd->next = (t_cmd *)calloc(1, sizeof(t_cmd));
				if (!cmd->next)
				{
					perror("Allocation failed");
					return ;
				}
				cmd->next->prev = cmd;
				cmd = cmd->next;
			}
		}
		else if (lex->token == GREATER || lex->token == D_GREATER
			|| lex->token == LOWER || lex->token == D_LOWER)
			handle_redirections(&lex, cmd, &redir_tail);
		else if (lex->token != WORD)
			append_command(cmd, lex->word);
		// Cas pour |>F| ou autres tokens spéciaux
		lex = lex->next;
	}
}

void	syntax_analyser(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			printf("Error: syntax error near unexpected token '|'\n");
			exit(1);
			// On peut aussi free les tokens et sortir de la boucle et non pas exit
		}
		if ((tmp->token == GREATER || tmp->token == D_GREATER
				|| tmp->token == LOWER || tmp->token == D_LOWER) && (!tmp->next
				|| tmp->next->token != WORD))
		{
			printf("Error: syntax error near unexpected token '%s'\n",
				tmp->word);
			exit(1);
			// On peut aussi free les tokens et sortir de la boucle et non pas exit
		}
		tmp = tmp->next;
	}
}

t_cmd	*rec_parse(t_lex *lex, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		perror("Allocation failed");
		return (NULL);
	}
	cmd->prev = prev;
	lex_loop(lex, cmd);
	return (cmd);
}

void	parser(t_cmd **cmd, t_lex *lex)
{
	syntax_analyser(lex);
	*cmd = rec_parse(lex, NULL);
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