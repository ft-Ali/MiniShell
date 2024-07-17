# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 16:29:26 by alsiavos          #+#    #+#              #
#    Updated: 2024/07/17 14:35:02 by alsiavos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_LIBFT = libft.a

CC = cc

FLAGS = -Wall -Wextra -Werror

FILES = 	ft_tolower.c \
		ft_toupper.c \
		ft_atoi.c \
		ft_atol.c \
		ft_bzero.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_strjoin.c \
		ft_freejoin.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_itoa.c \
		ft_split.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_strcmp.c \
		ft_free_split.c \
		ft_putchar.c \
		ft_isspace.c \
		ft_strndup.c \
		ft_strcpy.c \
		\
		./printf/ft_printf.c \
		./printf/ft_print_hexa.c \
		./printf/ft_print_int.c \
		./printf/ft_print_ptr.c \
		./printf/ft_print_usgnint.c \
		./printf/ft_print_basic.c \
		\
		./gnl/get_next_line.c \

OBJS = $(FILES:.c=.o)
	
.c.o:
	@printf "\r\033[K[libft] \033[0;32mCompilation : $<\033[0m"
	@$(CC) $(FLAGS) -c $< -o $@

all:	$(NAME_LIBFT)

$(NAME_LIBFT): $(OBJS)
	@printf "\r\033[K[libft] \033[0;32mLinking...\033[0m"
	@ar rc $(NAME_LIBFT) $(OBJS)
	@printf "\r\033[K[libft] \033[0;32mDone!\033[0m\n"

clean:
	@rm -f $(OBJS)
	@printf "[libft] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(NAME_LIBFT)
	@printf "[libft] \033[1;31mCleaned all!\033[0m\n"

re: fclean all

.PHONY: all clean fclean re