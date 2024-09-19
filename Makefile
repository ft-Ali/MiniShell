MINISHELL_NAME	=	minishell

CC			=	cc
FLAG		=	-Wall -Wextra -Werror -g3

LIBFT_PATH	=	.libft
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)
LIBS = -lreadline

MINISHELL_SRC	=	srcs/main.c srcs/lexer/lexer.c srcs/lexer/lexer_utils.c srcs/lexer/tokenize.c  \
					srcs/expander/expander.c srcs/expander/expander_utils.c srcs/parser/parser.c \
					srcs/env/env_setup.c srcs/env/env_management.c srcs/parser/parser_utils.c \
					srcs/env/env_list.c srcs/exec/exec.c srcs/utils/free_error.c srcs/utils/free_utils.c \
					srcs/utils/utils.c srcs/utils/prints.c srcs/exec/heredoc.c srcs/exec/redirections.c \
					srcs/exec/fds.c
					
					 

MINISHELL_OBJ	=	$(MINISHELL_SRC:.c=.o)


.c.o:
	@printf "\r\033[K[minishell] \033[0;32mBuilding : $<\033[0m\n"
	@$(CC) $(FLAG) -c $< -o $@

all:	$(MINISHELL_NAME)

# bonus:

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(MINISHELL_NAME): $(LIBFT_LIB) $(MINISHELL_OBJ) 
	@printf "\r\033[K[minishell] \033[0;32mLinking...\033[0m"
	@$(CC) $(MINISHELL_OBJ) $(LIBFT_LIB) -o $(MINISHELL_NAME) $(LIBS) -lm 
	@printf "\r\033[K[minishell] \033[0;32mDone!\033[0m\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -f $(MINISHELL_OBJ)
	@printf "[minishell] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(MINISHELL_NAME)
	@make fclean -C $(LIBFT_PATH)
	@printf "[minishell] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re