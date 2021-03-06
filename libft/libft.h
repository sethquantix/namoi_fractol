/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 18:14:30 by cchaumar          #+#    #+#             */
/*   Updated: 2016/10/23 07:21:41 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include "const.h"

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_circular
{
	void				*content;
	size_t				size;
	struct s_circular	*next;
	struct s_circular	*prev;
}				t_circular;

int				ft_isinside(int c, int low, int high);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *s, char c, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
size_t			ft_tabsize(char **s);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
void			ft_strtolower(char *s);
void			ft_strtoupper(char *s);
int				ft_tolower(int c);
int				ft_toupper(int c);
void			*ft_memalloc(size_t size);
void			ft_bzero(void *s, size_t n);
void			ft_memdel(void **ap);
void			ft_deltab(char **tab);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinfree(char const *s1, char const *s2, int mask);
int				ft_iswhite(char c);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_itoa_binary(int n, int base);
void			ft_print_bits(size_t const size, void const *const ptr);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(const char *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
int				ft_atoi(char *str);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstadd(t_list **alst, t_list *node);
void			ft_lstadd_end(t_list **alst, t_list *node);
size_t			ft_lstsize(t_list *root);
t_circular		*ft_circular_new(void *content, size_t size);
t_circular		*ft_circular_add_tail(t_circular **head, t_circular *node);
t_circular		*ft_circular_add_head(t_circular **head, t_circular *node);
t_circular		*ft_circular_find(t_circular *head, void *data,
	int (*f)(void *, void *));
void			ft_circular_delete_node(t_circular **head, t_circular *old);
void			ft_circular_free(t_circular **head);
void			ft_del(void *ptr, size_t size);
void			ft_lst_delif(t_list **root, t_list *node);
int				get_next_line(int const fd, char **line);
int				ft_printf(const char *format, ...);
int				ft_vaprintf(const char *format, va_list args);
int				ft_vasprintf(char **buff, const char *format, va_list args);
int				ft_sprintf(char **buff, const char *format, ...);

#endif
