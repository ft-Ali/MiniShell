/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/08/29 14:28:43 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------libft----------------*/

# include "../.libft/gnl/get_next_line.h"
# include "../.libft/libft.h"
# include "../.libft/printf/ft_printf.h"
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
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**commands;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

/*------------- EXPANDER PART -------------*/

typedef struct s_expand
{
	char			*input;
	char			*output;
	int				pos;
}					t_expand;

/*------------- ENV -------------*/

typedef struct s_env
{
	char			*value;
	char			*key;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/*------------- LEXER PART -------------*/

typedef struct s_lex
{
	char			*word;
	t_token			token;
	struct s_lex	*next;
}					t_lex;

/*------------- SHELL -------------*/
typedef struct s_shell
{
	t_env			*env;
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

void				expander(t_lex *token);
char				*strjoin_free(char *s1, char *s2);
char				*ft_strjoin_char(char *s, char c);
char				*expand_char(char *result, t_expand *exp);
int					handle_variable_expansion(t_expand *exp, char **result,
						char quote);
char				*expand_var(t_expand *exp);
void				handle_quotes(t_expand *exp, char *quote);

/*------------- LEXER -------------*/

t_lex				*lexer(t_shell *shell, char *string);
int					is_token(char *str, int i);
int					is_quote(char quote);
int					check_opened_quote(char *string);
void				add_new_word(t_shell *shell, t_lex **lexer, char *str,
						int indices[2]);
void				add_new_token(t_shell *shell, t_lex **lexer,
						int token_type);
void				exit_shell(t_shell *shell, char *error_msg);
void				free_tokens(t_lex *lexer);
// void				print_tokens(t_token *tokens);

/*---------------PARSER------------*/

void				parser(t_cmd **cmd, t_lex *lex);
t_cmd				*rec_parse(t_lex *lex, t_cmd *prev);
void				print_parser(t_cmd *cmd);

/*---------------ENV------------------*/
void				handle_no_env_vars(t_shell *shell);
void				set_env_vars(t_shell *shell, t_env *entry, char **envp,
						int index);
void				create_pwd(t_shell *shell);
void				add_env_entry(t_shell *shell, t_env *node, char **env_vars,
						int idx);
void				create_oldpwd(t_shell *shell);
void				load_env(t_shell *shell, char **env_vars);
char				*get_value_by_key(char *key, t_env *env_list);
char				**env_list_to_envp(t_env *env_list);
int					count_env_entries(t_env *env_list);

void				exec(t_shell *shell, t_cmd *cmd);
void				exec_cmds(t_shell *shell, t_cmd *cmd);

void				print_envp(char **envp);
#endif