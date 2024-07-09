/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:52 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/09 17:12:56 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

typedef enum e_token
{
	WORD,
	STRING,    // chaine de char
	PIPE,      // |
	GREATER,   // >
	D_GREATER, // >>
	LOWER,     // <
	D_LOWER,   // <<

}					t_token;

typedef struct s_lexer
{
	int				i;
	char			*str;
	t_token			token;
	struct s_lexer	*next;
}					t_lexer;

t_lexer				*new_token(t_token token, char *str);
void				add_token(t_lexer **lexer, t_token token, char *str);
void				tokenize(t_lexer **lexer, char *input);
void				print_tokens(t_lexer *lexer);
int					isRedirection(char c);
int					isPipe(char c);
void				word_string(t_lexer **lexer, char *input, int *i);
void				special_check(t_lexer **lexer, char *input, int *i);

#endif
