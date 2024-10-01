/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:04:22 by jpointil          #+#    #+#             */
/*   Updated: 2024/09/30 18:04:49 by jpointil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*(shell->excode = 2, exit_shell(shell,
				"Error: syntax error near unexpected token"));*/

void	lex_loop(t_shell *shell, t_lex *lex, t_cmd *cmd)
{
	t_redir	*redir_tail;

	redir_tail = NULL;
	while (lex)
	{
		if (lex->token == WORD)
			append_command(shell, cmd, lex->word);
		else if (lex->token == PIPE)
		{
			if (cmd->commands)
			{
				cmd->next = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
				if (!cmd->next)
					exit_shell(shell, A_ERR);
				cmd->next->prev = cmd;
				cmd = cmd->next;
			}
		}
		else if (lex->token == GREATER || lex->token == D_GREATER
			|| lex->token == LOWER || lex->token == D_LOWER)
			handle_redirections(shell, &lex, cmd, &redir_tail);
		lex = lex->next;
	}
}

void	check_redirection_error(t_shell *shell, t_lex *tmp)
{
	if ((tmp->token == GREATER || tmp->token == D_GREATER || tmp->token == LOWER
			|| tmp->token == D_LOWER) && (!tmp->next
			|| tmp->next->token != WORD))
	{
		shell->excode = 2;
		free_lex(tmp);
		exit_shell(shell, "Error: syntax error near unexpected token");
	}
}

void	syntax_analyser(t_shell *shell, t_lex *lex)
{
	t_lex	*tmp;

	if (!lex)
		return ;
	tmp = lex;
	if (tmp->token == PIPE)
	{
		shell->excode = 2;
		free_lex(lex);
		exit_shell(shell, "Error: syntax error near unexpected token");
	}
	while (tmp)
	{
		if (tmp->token == PIPE && (!tmp->next || tmp->next->token == PIPE))
		{
			shell->excode = 2;
			free_lex(lex);
			exit_shell(shell, "Error: syntax error near unexpected token");
		}
		check_redirection_error(shell, tmp);
		tmp = tmp->next;
	}
}

t_cmd	*rec_parse(t_shell *shell, t_lex *lex, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		exit_shell(shell, A_ERR);
	cmd->prev = prev;
	lex_loop(shell, lex, cmd);
	return (cmd);
}

void	parser(t_shell *shell, t_cmd **cmd, t_lex *lex)
{
	syntax_analyser(shell, lex);
	*cmd = rec_parse(shell, lex, NULL);
	free_lex(lex);
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