/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:19:59 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/12 15:45:33 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H
# include "lexer.h"
# include "minishell.h"
# include <stdbool.h>

typedef struct s_syntax
{
	struct s_syntax	*left;
	struct s_syntax	*right;
	struct s_syntax	*parent;
	char			*content;
	char			*type;
}					t_syntax;

typedef struct s_env
{
	char			*content;
	char			*var_name;
	bool			exported;
	struct s_env	*next;
}					t_env;

typedef struct s_expand
{
	char			*input;
	char			*output;
	int				pos;
}					t_expand;

/*------------- UTILS -------------*/

char				*strjoinfree(char *s1, char *s2);
static char			*extract_var_name(t_expand *exp);
char				*join_char(char *result, char char_to_join);
void				expander(t_token *token);
static char			*expand_var(t_expand *exp);
static char			*expand_char(char *result, t_expand *exp);
#endif