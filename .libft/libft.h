/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsiavos <alsiavos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:15:29 by alsiavos          #+#    #+#             */
/*   Updated: 2024/09/17 15:03:21 by alsiavos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_tolower(int c);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_putchar(char c);
void				ft_free_split(char **split);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strchr(const char *str, int tofound);
char				*ft_strnstr(const char *big, const char *small, size_t len);
char				*ft_strrchr(const char *str, int c);
char				*ft_strdup(const char *s);
void				ft_bzero(void *s, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
size_t				ft_strlcpy(char *dest, const char *src, size_t size);
size_t				ft_strlen(const char *s);
char				*ft_itoa(int nbr);
void				ft_putnbr_fd(int n, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_putendl_fd(char *s, int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strtrim(char const *s1, char const *set);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_free_n(char *s1, char *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_freejoin(char *s1, char *s2, int sizeS1, int sizeS2);
char				**ft_split(char const *s, char c);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_isspace(char c);
char				*ft_strndup(char *s, size_t len);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);

#endif