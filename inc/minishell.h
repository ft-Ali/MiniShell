/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpointil <jpointil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/18 15:06:16 by jpointil         ###   ########.fr       */
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

typedef enum e_token
{
	WORD,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_token;

typedef struct s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct s_redir
{
	t_token			token;
	char			*file;
}					t_redir;

typedef struct s_cmd // exec part
{
	char **commands;
	t_redir *redir;
	struct s_cmd *prev;
	struct s_cmd *next;
}					t_cmd;

typedef struct s_expand
{
	char *input;  // ce que readline lit = $HOME
	char *output; // ce qu'on va lui sortir $HOME = /home/alsiavos
	int pos;      // pour join et delete le $HOME et prendre que /home/alsiavos
}					t_expand;

/*------------- LEXER PART -------------*/

typedef struct s_lex
{
	char			*word;
	t_token			token;
	// int				ignore;
	struct s_lex	*next;
}					t_lex;

// typedef struct s_syntax
// {
// 	struct s_syntax	*left;
// 	struct s_syntax	*right;
// 	struct s_syntax	*parent;
// 	char			*content;
// 	char			*type;
// }					t_syntax;

typedef struct s_shell
// init shell a mettre les autres list ici puor tout set a 0 ?
{
	t_expand		*env;
	t_lex			*lex;
	t_path			*path;
	t_cmd			*cmd;
}					t_shell;

/*---------------colors--------------*/

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define CYAN "\033[1;96m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"

/*------------- EXPANDER -------------*/

char				*strjoin_free(char *s1, char *s2);
void				expander(t_lex *token);

/*------------- LEXER -------------*/

void				process_quote(char *string, int *index, int *count,
						int *quote_state);
t_lex				*lexer(t_shell *shell, char *string);
int					is_token(char *str, int i);
int					is_quote(char quote);
int					check_opened_quote(char *string);
void				add_new_word(t_shell *shell, t_lex **lexer, char *str,
						int indices[2]);
void				add_new_token(t_shell *shell, t_lex **lexer,
						int token_type);
void				exit_shell(t_shell *shell, char *error_msg);
// void				print_tokens(t_token *tokens);

/*---------------PARSER------------*/

void				parser(t_shell shell, t_lex *lex);

#endif