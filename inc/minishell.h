/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:19:16 by alsiavos          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/15 11:42:08 by alsiavos         ###   ########.fr       */
=======
/*   Updated: 2024/07/12 15:56:45 by alsiavos         ###   ########.fr       */
>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------libft----------------*/

# include "../.libft/gnl/get_next_line.h"
# include "../.libft/libft.h"
# include "../.libft/printf/ft_printf.h"
<<<<<<< HEAD
// # include "expander.h"
// # include "lexer.h"
=======

/*---------minishell headers---------*/

# include "expander.h"
# include "lexer.h"

/*-------------libraries-------------*/

>>>>>>> 6d34ad8ab7b6ad3e6b64b72696d3c0b20122e87a
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

typedef struct s_shell
{
	t_cmd			*cmds;
	// env
	//
}					t_shell;

typedef struct s_cmd
{
	char			**commands;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

/*---------------colors--------------*/

# define GREEN "\033[0;32m"
# define RED "\033[1;31m"
# define GREY "\033[0;90m"
# define CYAN "\033[1;96m"
# define RESET "\033[0m"
# define YELLOW "\033[0;33m"
# define PURPLE "\033[0;35m"
# define BOLD_PURPLE "\033[1;35m"

typedef enum e_token
{
	WORD,
	STRING,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_token;

typedef struct s_lexer
{
	int				i;
	char			*str;
	t_token			token;
	struct s_lexer	*next;
}					t_lexer;

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