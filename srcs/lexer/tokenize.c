/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:27:25 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/29 13:27:25 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	add_new_token(t_shell *shell, t_lex **lexer, int token_type)
{
	t_lex *new_token;
	t_lex *current;

	new_token = ft_calloc(1, sizeof(t_lex));
	if (!new_token)
		exit_shell(shell, "lexer malloc");
	new_token->word = NULL;
	new_token->token = token_type;
	if (!*lexer)
	{
		*lexer = new_token;
		new_token->next = NULL;
	}
	else
	{
		current = *lexer;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->next = NULL;
	}
}

void	add_new_word(t_shell *shell, t_lex **lexer, char *str, int indices[2])
{
	t_lex *new_word;
	t_lex *current;

	new_word = ft_calloc(1, sizeof(t_lex));
	if (!new_word)
		exit_shell(shell, "lexer malloc");
	new_word->word = ft_strndup(str + indices[0] - indices[1], indices[1]);
	new_word->token = 0;
	if (!*lexer)
	{
		*lexer = new_word;
		new_word->next = NULL;
	}
	else
	{
		current = *lexer;
		while (current->next)
			current = current->next;
		current->next = new_word;
		new_word->next = NULL;
	}
}

void	free_tokens(t_lex *lexer)
{
	t_lex *temp;

	while (lexer)
	{
		temp = lexer;
		lexer = lexer->next;
		if (temp->word)
			free(temp->word);
		free(temp);
	}
}

void	exit_shell(t_shell *shell, char *error_msg)
{
	if (shell->path)
		free(shell->path);
	if (shell->lex)
		free_tokens(shell->lex);
	perror(error_msg);
	free(shell);
	exit(EXIT_FAILURE);
}
