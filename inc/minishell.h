/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:59:41 by alsiavos          #+#    #+#             */
/*   Updated: 2024/10/04 13:02:03 by alsiavos         ###   ########.fr       */
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
# define A_ERR "Allocation error\n"

extern int			g_sig;

typedef enum e_token
{
	WORD,
	PIPE,
	GREATER,
	D_GREATER,
	LOWER,
	D_LOWER,
}					t_token;

typedef enum e_struct
{
	P,
	R,
	C,
	E,
	EN,
	L,
	S,
	PA
}					t_struct;

typedef struct s_norm
{
	char			*variable_name;
	char			*variable_value;
	char			*temp;
	bool			isfree;
	int				start;
}					t_norm;

typedef struct s_path
{
	char			*path_str;
	struct s_path	*next;
}					t_path;

typedef struct s_fd
{
	int				pipes[2];
	int				redir[2];
	int				input;
	int				output;
}					t_fd;

typedef struct s_redir
{
	t_token			token;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**commands;
	char			*cmd_path;
	t_redir			*redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

// typedef struct s_export
// {

// }

/*------------- ENV -------------*/

typedef struct s_env
{
	char			*value;
	char			*key;
	bool			isunset;
	int				index;
	struct s_env	*next;
	struct s_env	*prev;
}					t_env;

/*------------- EXPANDER -------------*/

typedef struct s_expand
{
	char			*input;
	char			*output;
	int				pos;
	t_env			*env;
}					t_expand;

/*------------- LEXER -------------*/

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
	int				tmpexcode;
	int				excode;
	t_path			*path;
	t_cmd			*cmd;
	char			*input;
	int				last_exit_status;
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

/*------------- MAIN -------------*/

void				exit_shell(t_shell *shell, char *error_msg);
void				init_sig(void);
bool				get_shell_sig(t_shell *shell);

/*------------- UTILS -------------*/

char				*strjoin_free(char *s1, char *s2);
char				*ft_strjoin_char(char *s, char c);
// int					find_end_index(const char *s1, const char *s2, int i);

/*------------- EXPANDER -------------*/

char				*expander(char *input, t_shell *shell);
char				*expand_char(char *result, char *input, int pos);
int					handle_variable_expansion(char *input, char **result,
						char quote, t_shell *shell);
char				*expand_var(char *input, int pos, t_shell *shell);
void				handle_quotes(char *exp, int *pos, char *quote);
t_lex				*trimquote_process(t_lex *lex);
size_t				count_char(char *str);
int					handle_variable_expansion_core(char *input, char **result,
						t_shell *shell, t_norm *norm);
int					handle_special_cases(char *input, char **result);
void				init_norm(t_norm *norm);

/*------------- LEXER -------------*/

t_lex				*lexer(t_shell *shell, char *string);
int					is_token(char *str, int i);
int					is_quote(char quote);
int					check_opened_quote(char *string);
void				add_new_word(t_shell *shell, t_lex **lexer, char *str,
						int indices[2]);
void				add_new_token(t_shell *shell, t_lex **lexer,
						int token_type);

/*--------------- PARSER ------------*/

void				parser(t_shell *shell, t_cmd **cmd, t_lex *lex);
t_cmd				*rec_parse(t_shell *shell, t_lex *lex, t_cmd *prev);
void				append_command(t_shell *shell, t_cmd *cmd, char *word);
void				handle_redirections(t_shell *shell, t_lex **lex, t_cmd *cmd,
						t_redir **redir_tail);
t_redir				*add_redir_node(t_shell *shell, t_token token, char *file);
int					syntax_analyser(t_shell *shell, t_lex *lex, t_lex *tmp);
void				lex_loop(t_shell *shell, t_lex *lex, t_cmd *cmd);

/*--------------- ENV ------------------*/

void				handle_no_env_vars(t_shell *shell);
void				set_env_vars(t_shell *shell, t_env *entry, char **envp,
						int index);
void				create_pwd(t_shell *shell);
void				add_env_entry(t_shell *shell, t_env *node, char **env_vars,
						int idx);
void				create_oldpwd(t_shell *shell);
void				load_env(t_shell *shell, char **env_vars);
char				*get_value_by_key(const char *key, t_env *env);
char				**env_list_to_envp(t_env *env_list, int i, int size);
int					count_env_entries(t_env *env_list);

/*------------- BUILTINS -------------*/

void				bi_exit(t_shell *shell, t_cmd *cmd);
void				bi_echo(t_shell *shell, t_cmd *cmd, int fd_out, t_fd *fd);
void				ft_putstr_fd_e(char *s, int fd, t_shell *shell);
void				bi_cd(t_shell *shell, t_cmd *cmd);
int					dir_check(t_shell *shell, t_cmd *cmd);
void				bi_env(t_shell *shell, t_cmd *cmd, int output, t_fd *fds);
void				bi_export(t_shell *shell, t_cmd *cmd);
void				add_or_update_env(t_env **env, const char *key,
						const char *value, t_shell *shell);
void				trim_spaces(char *str);
void				free_joined(char *str);
void				bi_pwd(t_shell *shell, t_cmd *cmd, int output, t_fd *fds);
void				bi_unset(t_shell *shell, t_cmd *cmd);

/*--------------- ERROR-&-FREE ------------------*/

void				free_lex(t_lex *lex);
void				free_path(t_path *path);
void				free_cmd(t_cmd *cmd);
void				free_exp(t_expand *expand);
void				free_redir(t_redir *redir);
void				free_shell(t_shell *shell);
void				free_env(t_env **env);
void				gfree(void *ptr, t_struct flag);
void				free_loop(t_shell *shell);
void				reset_loop(t_shell *shell);

/*--------------- PRINTS ------------------*/

void				print_env(t_env *env);
void				print_env_list(t_env *env_list);
void				print_tokens(t_lex *lex);
void				print_parser(t_cmd *cmd);
void				print_lexer_list(t_lex *head);

/*--------------- EXEC ------------------*/

char				*find_cmd_path(t_shell *shell, char *cmd);
void				exec(t_shell *shell, t_cmd *cmd);
void				exec_cmd(t_shell *shell, t_cmd *cmd, t_fd *fds,
						char **envp);
int					handle_input_redir(t_redir *redir, int fd_in,
						t_shell *shell);
int					handle_output_redir(t_redir *redir, int fd_out,
						t_shell *shell);
void				apply_redirections(t_cmd *cmd, int *fd_in, int *fd_out,
						t_shell *shell);
int					handle_heredoc(char *delimiter, t_shell *shell);
void				loop_here_doc(char *delimiter, int fd, t_shell *shell);
void				run_builtins(t_shell *shell, t_cmd *cmd, t_fd *fds);
void				child_builtins(t_shell *shell, t_fd *fds);
void				execute_child(t_shell *shell, t_cmd *cmd, t_fd *fds);
char				**get_paths_from_env(t_shell *shell);
void				execute_process(t_shell *shell, t_cmd *current_cmd,
						t_fd *fds);
int					handle_builtins(t_shell *shell, t_cmd *current_cmd);
void				init_fds_and_redirections(t_shell *shell,
						t_cmd *current_cmd, t_fd *fds);
int					is_builtin_command(const char *command);
int					is_dir(const char *path);
char				*get_cmd_path(t_shell *shell, t_cmd *cmd, t_fd *fds,
						char **envp);

/*--------------- FDS ------------------*/

void				init_fds(t_fd *fds);
void				set_fds(t_fd *fd);
void				close_fds_parent(t_fd *fds);
void				close_all_fds(t_fd *fds);
void				wait_child(t_shell *shell);
void				free_envp(char **envp);
// int					check_cmd_skip(t_shell *shell, t_cmd *cmd, int i);
char				*get_custom_env(t_env *env, char *var_name);
void				init_sig_heredoc(void);
#endif