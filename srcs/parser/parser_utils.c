/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:13 by jules             #+#    #+#             */
/*   Updated: 2024/09/09 16:42:14 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	redir->file = ft_strdup(file);
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
		(perror("Allocation failed"), return ());
	i = -1;
	while (cmd->commands && cmd->commands[++i])
		new_commands[i] = cmd->commands[i];
	if (!word)
	{
		new_commands[i] = NULL;
		return ;
	}
	new_commands[i] = ft_strdup(word);
	new_commands[i + 1] = NULL;
	if (cmd->commands)
		free(cmd->commands);
	cmd->commands = new_commands;
}