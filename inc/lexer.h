/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:52 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/12 13:35:13 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/* # include "minishell.h" */

// typedef enum e_comp
// {
// 	REDIR,
// 	PIPE,
// }					t_comp;

typedef enum e_type
{
	WORD,
	REDIR,
	STRING,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_type;

typedef struct s_token
{
	int				index;
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

void				add_token(t_token **lexer, t_type type, char *str);
void				tokenize(t_token **lexer, char *input);
void				print_tokens(t_token *lexer);
void				word(t_token **lexer, char *input, int *i);
int					special_check(t_token **lexer, char *input, int *i);
t_token				*new_token(t_type type, char *str);
int					is_or_not(char c, t_type comp);

#endif
