/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:06:52 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/11 18:01:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_tokentype
{
	WORD,
	STRING,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_tokentype;

typedef struct s_token
{
	int				i;
	char			*str;
	t_tokentype		type;
	struct s_token	*next;
}					t_token;

void				add_token(t_token **lexer, t_tokentype type, char *str);
void				tokenize(t_token **lexer, char *input);
void				print_tokens(t_token *lexer);
int					isredirection(char c);
int					ispipe(char c);
void				word(t_token **lexer, char *input, int *i);
int					special_check(t_token **lexer, char *input, int *i);
t_token				*new_token(t_tokentype type, char *str);

#endif
