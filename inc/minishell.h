/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:19:16 by alsiavos          #+#    #+#             */
/*   Updated: 2024/07/12 15:56:45 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*--------------libft----------------*/

# include "../.libft/gnl/get_next_line.h"
# include "../.libft/libft.h"
# include "../.libft/printf/ft_printf.h"

/*---------minishell headers---------*/

# include "expander.h"
# include "lexer.h"

/*-------------libraries-------------*/

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

#endif