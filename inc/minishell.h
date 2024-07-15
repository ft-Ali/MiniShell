/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/15 14:34:43 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------libft----------------*/

# include "../.libft/gnl/get_next_line.h"
# include "../.libft/libft.h"
# include "../.libft/printf/ft_printf.h"
// # include "expander.h"
// # include "lexer.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>

# define TRUE 0
# define FALSE -1
# define ERR_QUOTE "Error QUOTE\n"

typedef struct s_cmd
{
	char			**commands;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_path	*path;
	t_cmd	*cmd;
}			t_shell;

typedef enum e_token
{
	NOT_TOKEN,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_token;

typedef struct s_lex
{
	char			*word;
	bool			token;
	bool			redir;
	bool			quote;
	int				i;
	t_token			token;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

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

/*---------------colors--------------*/

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define CYAN "\033[1;96m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"

/*------------- UTILS -------------*/

char				*strjoinfree(char *s1, char *s2);
void				expander(t_lexer *token);

void				add_token(t_lexer **lexer, t_token token, char *str);
void				tokenize(t_lexer **lexer, char *input);
void				print_tokens(t_lexer *lexer);
int					isredirection(char c);
int					ispipe(char c);
void				word(t_lexer **lexer, char *input, int *i);
int					special_check(t_lexer **lexer, char *input, int *i);
t_lexer				*new_token(t_token token, char *str);

#endif