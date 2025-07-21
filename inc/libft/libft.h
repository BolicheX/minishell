/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-jim <jose-jim@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:53:21 by jose-jim          #+#    #+#             */
/*   Updated: 2025/07/20 20:45:37 by jose-jim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// buffer_size of gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// hexadecimal of ft_printf - putptr, puthexa
# define HEX_LOWCASE "0123456789abcdef"
# define HEX_UPCASE  "0123456789ABCDEF"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/* -------◊		FUNCTIONS TO CONVERSION/INTEGERS	◊------- */
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);

/* -------◊	FUNCTIONS TO MANIPULATE CHARACTERS	◊------- */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isnum(char *s);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_putchar(int c);
int		ft_putstr(char *str);
int		ft_putptr(unsigned long n);
int		ft_putnbr(int nb);
int		ft_putnbr_unsign(unsigned int n);
int		ft_puthex(unsigned int number, int conv);
int		ft_countchar(const char *str, char c);

/* -------◊	FUNCTIONS TO MANIPULATE STRINGS	◊------- */
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strrncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/* -------◊		FUNCTIONS TO MANIPULATE MEMORY	◊------- */
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(const char *s);

/* -------◊		FUNCTIONS FILE DESCRIPTOR     ◊------- */
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_countlines_fd(int fd);

/* -------◊		FUNCTIONS MATH     ◊------- */
int		ft_mean(int *n, int size);
int		ft_abs(int a);
int		ft_max_i(int *arr, int size);
int		ft_max_2(int a, int b);
int		ft_min_i(int *arr, int size);

/* -------◊	LINKED LISTS	◊------- */
typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list  *ft_lstnew(void *content);
void    ft_lstadd_front(t_list **lst, t_list *new);
void    ft_lstadd_back(t_list **lst, t_list *new);
t_list  *ft_lstlast(t_list *lst);
int	    ft_lstsize(t_list *lst);
void    ft_lstdelone(t_list *node, void (*del)(void *));
void    ft_lstclear(t_list **lst, void (*del)(void	*));
void    ft_lstiter(t_list *lst, void (*f)(void *));
t_list  *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* -------◊	KEY-VALUE LISTS	◊------- */
typedef struct	s_kvl
{
	char			*key;
	void			*value;
	struct s_kvl	*next;
}					t_kvl;

t_kvl	*ft_kvl_new(char *key, void *value);
int    ft_kvl_add(t_kvl **lst, t_kvl *new);
void	*ft_kvl_set(t_kvl **lst, char *key, void *value);
void	*ft_kvl_get(t_kvl *lst, char *key);
void	ft_kvl_iter(t_kvl *lst, void (*f)(char *, void *));
void	ft_kvl_delone(t_kvl *node, void (*del)(void    *));
t_kvl	*ft_kvl_clear(t_kvl **lst, void (*del)(void    *));
int		ft_kvl_remove(t_kvl **lst, char *key, void (*del)(void    *));

/* -------◊	PRINTF	◊------- */
int		ft_printf(const char *s, ...);
int		format(char conv, va_list arg);

/* -------◊	GNL	◊------- */
char	*add_buff(int fd, char *save, char *buff);
char	*cut_line(char **save);
char	*get_next_line(int fd);

#endif
